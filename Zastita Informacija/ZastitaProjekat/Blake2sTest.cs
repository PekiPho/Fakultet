using FileTransfer.Crypto;
using System;
using System.IO;
using System.Linq;
using System.Text;
using ZastitaProjekat.Algorithms;

namespace ZastitaProjekat
{
     class Blake2sTest
    {
        public static void Run()
        {
            string text = string.Concat(Enumerable.Repeat(
        "The quick brown fox jumps over the lazy dog. ", 5));
            byte[] data = System.Text.Encoding.UTF8.GetBytes(text);

            byte[] hashMine = ZastitaProjekat.Algorithms.Blake2s.ComputeHash(data);

            byte[] hashHers = FileTransfer.Crypto.Blake2Hash.ComputeHash(data);

            Console.WriteLine("Your Blake2s: " + Convert.ToHexString(hashMine));
            Console.WriteLine("Her Blake2s:  " + Convert.ToHexString(hashHers));

            Console.WriteLine(hashMine.SequenceEqual(hashHers) ? "MATCH ✅" : "DIFFERENT ❌");
        }

        public static void RunXTEA()
        {
            string text = "The quick brown fox jumps over the lazy dog. ";
            byte[] data = Encoding.UTF8.GetBytes(string.Concat(Enumerable.Repeat(text, 3)));

            byte[] key = FileTransfer.Crypto.CryptoConfig.Key;
            byte[] iv = FileTransfer.Crypto.CryptoConfig.IV;

            byte[] dataMine = (byte[])data.Clone();
            ZastitaProjekat.Algorithms.XTEA.Process(dataMine, key, iv);

            byte[] dataHers = XteaOfb.Encrypt(data, key);

            Console.WriteLine("Your OFB/XTEA: " + Convert.ToHexString(dataMine));
            Console.WriteLine("Her OFB/XTEA:  " + Convert.ToHexString(dataHers));
            Console.WriteLine(dataMine.SequenceEqual(dataHers) ? "MATCH ✅" : "DIFFERENT ❌");
        }
    }
}
