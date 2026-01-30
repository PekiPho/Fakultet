using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Security.Cryptography.Xml;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
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
            if(!Directory.Exists(OutputDirectory))
                Directory.CreateDirectory(OutputDirectory);
        }

        public void ProtectFile(string filePath,string algo, byte[] key, byte[] iv)
        {
            try
            {
                log.Log("Kriptovanje", $"Pokretanje za: {Path.GetFileName(filePath)} , {algo}");
                byte[] data = File.ReadAllBytes(filePath);
                byte[] hashValue = Blake2s.ComputeHash(data);

                if (algo.ToUpper() == "XTEA")
                {
                    XTEA.Process(data, key, iv);
                }
                else
                {
                    A51 a5 = new A51();
                    ulong uKey = BitConverter.ToUInt64(key, 0);
                    a5.Initialize(uKey);
                    a5.Process(data);
                }

                var metadata = new FileMetadata
                {
                    FileName = Path.GetFileName(filePath),
                    FileSize = data.Length,
                    CreationTime = DateTime.Now,
                    EncryptionAlgo = algo,
                    HashAlgo = "BLAKE2s",
                    HashValue = hashValue,
                    IV = iv
                };

                SavePackage(metadata, data);
            }
            catch(Exception ex)
            {
                log.Log("Greska", $"Kriptovanje neuspesno: {ex.Message}", "Fail");
            }
        }


        public void UnprotectFile(string protectedFilePath, byte[] key)
        {
            try
            {
                using (FileStream fs = new FileStream(protectedFilePath, FileMode.Open, FileAccess.Read))
                {
                    byte[] lenBuf = new byte[4];
                    fs.Read(lenBuf, 0, 4);
                    int headerLen = BitConverter.ToInt32(lenBuf, 0);

                    byte[] headBuf = new byte[headerLen];
                    fs.Read(headBuf, 0, headerLen);
                    var metadata = JsonSerializer.Deserialize<FileMetadata>(Encoding.UTF8.GetString(headBuf));

                    byte[] data = new byte[fs.Length - fs.Position];
                    fs.Read(data, 0, data.Length);

                    if (metadata.EncryptionAlgo.ToUpper() == "XTEA")
                    {
                        XTEA.Process(data, key, metadata.IV);
                    }
                    else
                    {
                        A51 a5 = new A51();
                        ulong uKey = BitConverter.ToUInt64(key, 0);
                        a5.Initialize(uKey);
                        a5.Process(data);
                    }

                    byte[] currentHash = Blake2s.ComputeHash(data);
                    if (!StructuralComparisons.StructuralEqualityComparer.Equals(metadata.HashValue, currentHash))
                    {
                        throw new Exception("Hash se ne poklapa!");
                    }

                    string outPath = Path.Combine(OutputDirectory, "DECRYPTED_" + metadata.FileName);
                    File.WriteAllBytes(outPath, data);
                    log.Log("Uspesno", $"Fajl {metadata.FileName} je dekriptovan");
                }
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

            string outPath = Path.Combine(OutputDirectory, metadata.FileName + ".protected");

            using (FileStream fs = new FileStream(outPath, FileMode.Create))
            {
                fs.Write(headLen, 0, 4);
                fs.Write(headBytes, 0, headBytes.Length);
                fs.Write(encryptedContent, 0, encryptedContent.Length);
            }
            log.Log("Uspeh", $"Fajl stavljen u: {Path.GetFileName(outPath)}");
        }
    }
}
