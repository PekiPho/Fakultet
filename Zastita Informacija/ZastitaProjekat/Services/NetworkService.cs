using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ZastitaProjekat.Services
{
    public class NetworkService
    {

        private readonly LogService log;
        private TcpListener tcpListener;
        private bool isListening;
        private const int Port = 8080;


        public NetworkService(LogService log)
        {
            this.log = log;
        }

        public async Task StartReceiving(string saveDirectory)
        {
            try
            {
                tcpListener = new TcpListener(IPAddress.Any, Port);
                tcpListener.Start();
                isListening = true;
                log.Log("Mreza", $"Server pokrenut, slusa se na {Port}");

                while (isListening)
                {
                    using (TcpClient client = await tcpListener.AcceptTcpClientAsync())
                    using (NetworkStream stream = client.GetStream())
                    {
                        log.Log("Mreza", "Konekcija prihvacena, prihvatanje fajla");

                        byte[] nameLenBuf = new byte[4];
                        await stream.ReadAsync(nameLenBuf, 0, 4);
                        int nameLen = BitConverter.ToInt32(nameLenBuf, 0);

                        byte[] nameBuf = new byte[nameLen];
                        await stream.ReadAsync(nameBuf, 0, nameLen);
                        string fileName = System.Text.Encoding.UTF8.GetString(nameBuf);

                        string fullPath = Path.Combine(saveDirectory, fileName);

                        using (FileStream fs = new FileStream(fullPath, FileMode.Create))
                        {
                            await stream.CopyToAsync(fs);
                        }

                        log.Log("Mreza", $"Fajl primljen i sacuvan: {fileName}");
                    }
                }
            }
            catch (Exception ex)
            {
                if (isListening)
                    log.Log("Mreza", $"Greska pri prijemu: {ex.Message}","Fail");
            }
        }

        public void StopReceiving()
        {
            isListening = false;
            tcpListener?.Stop();
            log.Log("Mreza", "Server zaustavljen");
        }

        public async Task SendFile(string ipAddress, string filePath)
        {
            try
            {
                log.Log("Slanje", $"Salje se na: {ipAddress}");

                using(TcpClient client = new TcpClient())
                {
                    await client.ConnectAsync(ipAddress, Port);

                    using(NetworkStream stream = client.GetStream())
                    {
                        byte[] fileData = File.ReadAllBytes(filePath);
                        byte[] fileNameBytes = System.Text.Encoding.UTF8.GetBytes(Path.GetFileName(filePath));
                        byte[] fileNameLen = BitConverter.GetBytes(fileNameBytes.Length);

                        await stream.WriteAsync(fileNameLen, 0, 4);
                        await stream.WriteAsync(fileNameBytes, 0, fileNameBytes.Length);
                        await stream.WriteAsync(fileData, 0, fileData.Length);
                    }
                }

                log.Log("Slanje", "Fajl uspesno poslat!!");
            }
            catch(Exception ex)
            {
                log.Log("Slanje", $"Slanje neuspesno: {ex.Message}", "Fail");
            }
        }
    }
}
