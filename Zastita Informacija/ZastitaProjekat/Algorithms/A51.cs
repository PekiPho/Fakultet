using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZastitaProjekat.Algorithms
{
    public class A51
    {
        private uint regX,regY,regZ;


        public void Initialize(byte[] key)
        {
            regX = 0;
            regY = 0;
            regZ = 0;

            foreach (byte b in key)
            {
                for (int i = 0; i < 8; i++)
                {
                    int bit = (b >> i) & 1;
                    regX = ((regX << 1) | (uint)bit) & 0x7FFFF;
                    regY = ((regY << 1) | (uint)bit) & 0x3FFFFF;
                    regZ = ((regZ << 1) | (uint)bit) & 0x7FFFFF;
                }
            }

            for (int i = 0; i < 100; i++)
            {
                GenerateByte();
            }
        }

        private uint GetMajority(uint x8, uint y10, uint z10)
        {
            return (x8 + y10 + z10) > 1 ? 1u : 0u;
        }

        public byte GenerateByte()
        {
            byte res = 0;

            for (int i = 0; i < 8; i++)
            {
                uint majority = GetMajority((regX >> 8) & 1, (regY >> 10) & 1, (regZ >> 10) & 1);

                if (((regX >> 8) & 1) == majority)
                {
                    uint poslednja = ((regX >> 18) ^ (regX >> 17) ^ (regX >> 16) ^ (regX >> 13)) & 1;
                    regX = ((regX << 1) & 0x7FFFF) | poslednja;
                }

                if (((regY >> 10) & 1) == majority)
                {
                    uint poslednja = ((regY >> 21) ^ (regY >> 20)) & 1;
                    regY = ((regY << 1) & 0x3FFFFF) | poslednja;
                }

                if (((regZ >> 10) & 1) == majority)
                {
                    uint poslednja = ((regZ >> 22) ^ (regZ >> 21) ^ (regZ >> 20) ^ (regZ >> 7)) & 1;
                    regZ = ((regZ << 1) & 0x7FFFFF) | poslednja;
                }

                uint bit = ((regX>>18)^(regY>>21)^(regZ>>22)) & 1;
                res |= (byte)(bit << i);

            }

            return res;
        }

        public void Process(byte[] data)
        {
            for (int i = 0; i < data.Length; i++)
            {
                data[i] ^= GenerateByte();
            }
        }
    }
}
