using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZastitaProjekat.Algorithms
{
    public class Blake2s
    {
        private static readonly uint[] IV =
        {
            0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
            0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19
        };

        private static readonly byte[,] Sigma =
        {
            { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
            { 14, 10, 4, 8, 9, 15, 13, 6, 1, 12, 0, 2, 11, 7, 5, 3 },
            { 11, 8, 12, 0, 5, 2, 15, 13, 10, 14, 3, 6, 7, 1, 9, 4 },
            { 7, 9, 3, 1, 13, 12, 11, 14, 2, 6, 5, 10, 4, 0, 15, 8 },
            { 9, 0, 5, 7, 2, 4, 10, 15, 14, 1, 11, 12, 6, 8, 3, 13 },
            { 2, 12, 6, 10, 0, 11, 8, 3, 4, 13, 7, 5, 15, 14, 1, 9 },
            { 12, 5, 1, 15, 14, 13, 4, 10, 0, 7, 6, 3, 9, 2, 8, 11 },
            { 13, 11, 7, 14, 12, 1, 3, 9, 5, 0, 15, 4, 8, 6, 2, 10 },
            { 6, 15, 14, 9, 11, 3, 0, 8, 12, 2, 13, 7, 1, 4, 10, 5 },
            { 10, 2, 8, 4, 7, 6, 1, 5, 15, 11, 9, 14, 3, 12, 13, 0 }
        };

        private static void G(uint[] v,int a,int b,int c,int d,uint x,uint y)
        {
            v[a] = v[a] + v[b] + x;
            v[d] = RotateRight(v[d] ^ v[a], 16);
            v[c] = v[c] + v[d];
            v[b] = RotateRight(v[b] ^ v[c], 12);
            v[a] = v[a] + v[b] + y;
            v[d] = RotateRight(v[d] ^ v[a], 8);
            v[c] = v[c] + v[d];
            v[b] = RotateRight(v[b] ^ v[c], 7);

        }

        private static uint RotateRight(uint v,int n)
        {
            return (v >> n) | (v << (32 - n));
        }

        private static void F(uint[] h, uint[] m,ulong t,bool isLastBlock)
        {
            uint[] v = new uint[16];
            Array.Copy(h, 0, v, 0, 8);
            Array.Copy(IV, 0, v, 8, 8);

            v[12] ^= (uint)t;
            v[13] ^= (uint)(t >> 32);

            if(isLastBlock )
            {
                v[14] = ~v[14];
            }

            for(int r = 0; r < 10; r ++)
            {
                G(v, 0, 4, 8, 12, m[Sigma[r, 0]], m[Sigma[r, 1]]);
                G(v, 1, 5, 9, 13, m[Sigma[r, 2]], m[Sigma[r, 3]]);
                G(v, 2, 6, 10, 14, m[Sigma[r, 4]], m[Sigma[r, 5]]);
                G(v, 3, 7, 11, 15, m[Sigma[r, 6]], m[Sigma[r, 7]]);
                G(v, 0, 5, 10, 15, m[Sigma[r, 8]], m[Sigma[r, 9]]);
                G(v, 1, 6, 11, 12, m[Sigma[r, 10]], m[Sigma[r, 11]]);
                G(v, 2, 7, 8, 13, m[Sigma[r, 12]], m[Sigma[r, 13]]);
                G(v, 3, 4, 9, 14, m[Sigma[r, 14]], m[Sigma[r, 15]]);
            }

            for(int i = 0; i < 8; i++)
            {
                h[i] ^= v[i] ^ v[i + 8];
            }
        }

        public static byte[] ComputeHash(byte[] data)
        {
            uint[] h = (uint[])IV.Clone();
            h[0] ^= 0x01010020;

            int offset = 0;
            while (offset + 64 < data.Length)
            {
                uint[] m = new uint[16];
                Buffer.BlockCopy(data, offset, m, 0, 64);
                offset += 64;
                F(h, m, (ulong)offset, false);
            }

            uint[] finalM=new uint[16];
            int remaining = data.Length - offset;
            Buffer.BlockCopy(data,offset,finalM, 0, remaining);
            F(h, finalM, (ulong)data.Length, true);

            byte[] res = new byte[32];
            Buffer.BlockCopy(h, 0, res, 0, 32);
            return res;
        }
    }
}
