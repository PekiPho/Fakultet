using FileTransfer.Crypto;
using FileTransfer.Services;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using ZastitaProjekat.Algorithms;
using ZastitaProjekat.Models;
using XTEA = ZastitaProjekat.Algorithms.XTEA;

namespace ZastitaProjekat.Services
{
    public class NetworkService
    {

        private readonly LogService log;
        private TcpListener tcpListener;
        private readonly FileService fileService;
        private bool isListening;
        private const int Port = 9000;
        private byte[] currentKey;


        public NetworkService(LogService log, FileService fileService)
        {
            this.log = log;
            this.fileService = fileService;
        }

        public async Task StartReceiving(string saveDirectory, byte[] key)
        {
            try
            {
                this.currentKey = key;
                tcpListener = new TcpListener(IPAddress.Any, Port);
                tcpListener.Start();
                isListening = true;
                log.Log("Mreza", $"Server started, listening on {Port}");

                while (isListening)
                {
                    using TcpClient client = await tcpListener.AcceptTcpClientAsync();
                    using NetworkStream stream = client.GetStream();

                    byte[] totalLenBuf = new byte[4];
                    await ReadExactAsync(stream, totalLenBuf, 4);
                    int totalLen = BitConverter.ToInt32(totalLenBuf);

                    byte[] packet = new byte[totalLen];
                    await ReadExactAsync(stream, packet, totalLen);

                    int offset = 0;

                    int metaLen = BitConverter.ToInt32(packet, offset);
                    offset += 4;

                    byte algId = packet[offset];
                    offset += 1;

                    string json = Encoding.UTF8.GetString(packet, offset, metaLen);
                    offset += metaLen;
                    var metadata = JsonSerializer.Deserialize<FileMetadata>(json);

                    int encryptedLen = totalLen - offset - 32;
                    byte[] encryptedData = new byte[encryptedLen];
                    Buffer.BlockCopy(packet, offset, encryptedData, 0, encryptedLen);

                    byte[] receivedHash = new byte[32];
                    Buffer.BlockCopy(packet, offset + encryptedLen, receivedHash, 0, 32);

                    byte[] computedHash = Blake2Hash.ComputeHash(encryptedData);
                    if (!computedHash.SequenceEqual(receivedHash))
                        throw new Exception("Hash mismatch!");

                    if (algId == 1)
                    {
                        XTEA.Process(encryptedData, currentKey);
                    }
                    else
                    {
                        var a5 = new A51();
                        a5.Initialize(currentKey);
                        a5.Process(encryptedData);
                    }

                    Directory.CreateDirectory(saveDirectory);
                    string finalPath = Path.Combine(saveDirectory, metadata.FileName);

                    await File.WriteAllBytesAsync(finalPath, encryptedData);

                    log.Log("Mreza", $"File received and decrypted: {metadata.FileName}", "Success");
                }
            }
            catch (Exception ex)
            {
                if (isListening)
                    log.Log("Mreza", $"Error during reception: {ex.Message}", "Fail");
            }
        }





        private static async Task ReadExactAsync(NetworkStream stream, byte[] buffer, int size)
        {
            int totalRead = 0;
            while (totalRead < size)
            {
                int read = await stream.ReadAsync(buffer, totalRead, size - totalRead);
                if (read == 0)
                    throw new Exception("Connection closed unexpectedly.");
                totalRead += read;
            }
        }

        public void StopReceiving()
        {
            isListening = false;
            tcpListener?.Stop();
            log.Log("Mreza", "Server zaustavljen");
        }

        public async Task SendFile(string ipAddress, string filePath, byte[] key, string cipherMode)
        {
            try
            {
                var service = new SecureTransferService();
                byte[] packet = service.ProtectFile(filePath, key, cipherMode);

                using TcpClient client = new TcpClient();
                await client.ConnectAsync(ipAddress, Port);

                using NetworkStream stream = client.GetStream();

                byte[] lengthBytes = BitConverter.GetBytes(packet.Length);
                await stream.WriteAsync(lengthBytes, 0, lengthBytes.Length);

                await stream.WriteAsync(packet, 0, packet.Length);

                await stream.FlushAsync();

                log.Log("Mreza", $"File sent successfully to {ipAddress}", "Success");
            }
            catch (Exception ex)
            {
                log.Log("Mreza", $"Error sending file to {ipAddress}: {ex.Message}", "Fail");
            }
        }


    }
}
