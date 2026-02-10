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

namespace ZastitaProjekat.Services
{
    public class NetworkService
    {

        private readonly LogService log;
        private TcpListener tcpListener;
        private readonly FileService fileService;
        private bool isListening;
        private const int Port = 8080;
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
                    using (TcpClient client = await tcpListener.AcceptTcpClientAsync())
                    using (NetworkStream stream = client.GetStream())
                    {
                        byte[] totalLenBuf = new byte[4];
                        await ReadExactAsync(stream, totalLenBuf, 4);
                        int totalLen = BitConverter.ToInt32(totalLenBuf);

                        byte[] packet = new byte[totalLen];
                        await ReadExactAsync(stream, packet, totalLen);

                        string tempPath = Path.Combine(saveDirectory, "incoming.protected");
                        await File.WriteAllBytesAsync(tempPath, packet);

                        fileService.UnprotectFile(tempPath, currentKey);
                    }
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

        public async Task SendFile(string ipAddress, string filePath, string algo, byte[] key, byte[] iv)
        {
            try
            {
                byte[] originalData = File.ReadAllBytes(filePath);
                byte[] hashValue = Blake2s.ComputeHash(originalData);
                byte[] dataToEncrypt = (byte[])originalData.Clone();

                byte algId = (byte)(algo.ToUpper().Contains("A5") ? 2 : 1);
                if (algId == 1)
                {
                    XTEA.Process(dataToEncrypt, key, iv);
                }
                else
                {
                    A51 a5 = new A51();
                    a5.Initialize(key);
                    a5.Process(dataToEncrypt);
                }

                var metadata = new FileMetadata
                {
                    FileName = Path.GetFileName(filePath),
                    FileSize = originalData.Length,
                    EncryptionAlgo = algo,
                    HashValue = hashValue,
                    IV = iv
                };

                string json = JsonSerializer.Serialize(metadata);
                byte[] metaBytes = Encoding.UTF8.GetBytes(json);
                byte[] metaLen = BitConverter.GetBytes(metaBytes.Length);

                using (var ms = new MemoryStream())
                {
                    ms.Write(metaLen, 0, 4);
                    ms.WriteByte(algId);
                    ms.Write(metaBytes, 0, metaBytes.Length);
                    ms.Write(dataToEncrypt, 0, dataToEncrypt.Length);

                    byte[] finalPacket = ms.ToArray();
                    byte[] totalLen = BitConverter.GetBytes(finalPacket.Length);

                    using (TcpClient client = new TcpClient())
                    {
                        await client.ConnectAsync(ipAddress, Port);
                        using (NetworkStream stream = client.GetStream())
                        {
                            await stream.WriteAsync(totalLen, 0, 4);
                            await stream.WriteAsync(finalPacket, 0, finalPacket.Length);
                        }
                    }
                }
                log.Log("Mreza", "Packet sent with Total Length and AlgID!", "Success");
            }
            catch (Exception ex) { log.Log("Greska", ex.Message, "Fail"); }
        }

    }
}
