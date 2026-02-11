using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZastitaProjekat.Algorithms
{
    public class XTEA
    {
        private const int Runde = 32;
        private const uint Delta = 0x9E3779B9;

        private static readonly byte[] IV = new byte[]
        {
            0x01, 0x23, 0x45, 0x67,
            0x89, 0xAB, 0xCD, 0xEF
        };


        public static void Encrypt(uint[] v, uint[] key)
        {
            uint v0 = v[0], v1 = v[1];
            uint sum = 0;

            for (int i = 0; i < Runde; i++)
            {
                v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
                sum += Delta;
                v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
            }

            v[0] = v0;
            v[1] = v1;
        }


        public static void Decrypt(uint[] v, uint[] key)
        {
            uint v0 = v[0],v1 = v[1];

            uint sum;
            unchecked
            {
                sum = Delta * Runde;
            }

            for(int i = 0;i < Runde;i++)
            {
                v1-= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
                sum -= Delta;
                v0-= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
            }

            v[0] = v0;
            v[1] = v1;
        }


        public static void Process(byte[] data, byte[] keyBytes)
        {
            uint[] key = new uint[4];
            uint[] vector = new uint[2];

            int keyLen = Math.Min(keyBytes.Length, 16);
            Buffer.BlockCopy(keyBytes, 0, key, 0, keyLen);

            Buffer.BlockCopy(IV, 0, vector, 0, IV.Length);

            for (int i = 0; i < data.Length; i += 8)
            {
                Encrypt(vector, key);

                byte[] mask = new byte[8];
                Buffer.BlockCopy(vector, 0, mask, 0, 8);

                for (int j = 0; j < 8 && (i + j) < data.Length; j++)
                {
                    data[i + j] ^= mask[j];
                }
            }
        }
    }
}
