using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using ZastitaProjekat.Algorithms;
using ZastitaProjekat.Models;

namespace ZastitaProjekat.Services
{
    public class FileService
    {
        private readonly LogService log;
        private static readonly string BasePath = AppDomain.CurrentDomain.BaseDirectory;
        private readonly string OutputDirectory = Path.Combine(BasePath, "Output");

        public FileService(LogService logService)
        {
            log = logService;
            if (!Directory.Exists(OutputDirectory))
                Directory.CreateDirectory(OutputDirectory);
        }

        public void ProtectFile(string filePath, string algo, byte[] key, byte[] iv)
        {
            try
            {
                log.Log("Kriptovanje", $"Pokretanje za: {Path.GetFileName(filePath)} , {algo}");

                byte[] originalData = File.ReadAllBytes(filePath);
                long originalLength = originalData.Length;

                byte[] hashValue = Blake2s.ComputeHash(originalData);

                byte[] dataToEncrypt = originalData;

                if (algo.ToUpper().Contains("XTEA"))
                {
                    int remainder = originalData.Length % 8;
                    if (remainder != 0)
                    {
                        dataToEncrypt = new byte[originalData.Length + (8 - remainder)];
                        Array.Copy(originalData, 0, dataToEncrypt, 0, originalData.Length);
                    }
                    XTEA.Process(dataToEncrypt, key, iv);
                }
                else if (algo.ToUpper().Contains("A5"))
                {
                    A51 a5 = new A51();
                    a5.Initialize(key);
                    a5.Process(dataToEncrypt);
                }

                string cipherMode = algo.ToUpper().Contains("A5") ? "A5/1" : "XTEA+OFB";

                var metadata = new FileMetadata
                {
                    FileName = Path.GetFileName(filePath),
                    FileSize = originalLength,
                    CreationTime = DateTime.Now,
                    EncryptionAlgo = algo,
                    CipherMode = cipherMode,
                    HashAlgo = "BLAKE2s",
                    HashValue = hashValue,
                    IV = iv
                };

                SavePackage(metadata, dataToEncrypt);
                log.Log("Kriptovanje", "Uspesno kreiran .protected paket", "Success");
            }
            catch (Exception ex)
            {
                log.Log("Greska", $"Kriptovanje neuspesno: {ex.Message}", "Fail");
            }
        }

        public void UnprotectFile(string protectedFilePath, byte[] key)
        {
            try
            {
                byte[] allBytes = File.ReadAllBytes(protectedFilePath);

                int headerLen = BitConverter.ToInt32(allBytes, 0);

                byte algId = allBytes[4];

                byte[] headBuf = new byte[headerLen];
                Array.Copy(allBytes, 5, headBuf, 0, headerLen);

                var metadata = JsonSerializer.Deserialize<FileMetadata>(Encoding.UTF8.GetString(headBuf));

                int dataPos = 5 + headerLen;
                int hashSize = 32; 
                int dataLen = allBytes.Length - dataPos - hashSize;

                byte[] data = new byte[dataLen];
                Array.Copy(allBytes, dataPos, data, 0, dataLen);

                byte[] receivedHash = new byte[hashSize];
                Array.Copy(allBytes, dataPos + dataLen, receivedHash, 0, hashSize);

                byte[] computedHash = Blake2s.ComputeHash(data);
                if (!computedHash.SequenceEqual(receivedHash))
                    throw new Exception("Integritet narusen! Hash se ne poklapa.");

                if (algId == 1 || metadata.CipherMode.ToUpper().Contains("XTEA"))
                {
                    XTEA.Process(data, key, metadata.IV);
                }
                else if (algId == 2 || metadata.CipherMode.ToUpper().Contains("A5"))
                {
                    A51 a5 = new A51();
                    a5.Initialize(key);
                    a5.Process(data);
                }

                byte[] finalData = new byte[metadata.FileSize];
                Array.Copy(data, 0, finalData, 0, (int)metadata.FileSize);

                string outPath = Path.Combine(OutputDirectory, "DECRYPTED_" + metadata.FileName);
                File.WriteAllBytes(outPath, finalData);

                log.Log("Uspeh", $"Fajl {metadata.FileName} dekriptovan i verifikovan!");
            }
            catch (Exception ex)
            {
                log.Log("Greska", $"Dekriptovanje neuspesno: {ex.Message}", "Fail");
            }
        }



        private void SavePackage(FileMetadata metadata, byte[] encryptedContent)
        {
            string json = JsonSerializer.Serialize(metadata);
            byte[] headBytes = Encoding.UTF8.GetBytes(json);
            byte[] headLen = BitConverter.GetBytes(headBytes.Length);

            byte algId = (byte)(metadata.EncryptionAlgo.ToUpper().Contains("A5") ? 2 : 1);

            string outPath = Path.Combine(OutputDirectory, metadata.FileName + ".protected");

            byte[] hashValue = Blake2s.ComputeHash(encryptedContent);

            using (FileStream fs = new FileStream(outPath, FileMode.Create))
            {
                fs.Write(headLen, 0, headLen.Length);
                fs.WriteByte(algId);
                fs.Write(headBytes, 0, headBytes.Length);
                fs.Write(encryptedContent, 0, encryptedContent.Length);
                fs.Write(hashValue, 0, hashValue.Length);
            }

            log.Log("Uspeh", $"Zasticen fajl kreiran: {Path.GetFileName(outPath)}");
        }
    }
}