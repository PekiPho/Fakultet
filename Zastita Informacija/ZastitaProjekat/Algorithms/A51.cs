using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZastitaProjekat.Algorithms
{
    public class A51
    {
        private uint X;
        private uint Y;
        private uint Z;

        private const uint X_MASK = 0x7FFFF;
        private const uint Y_MASK = 0x3FFFFF;
        private const uint Z_MASK = 0x7FFFFF;

        public void Initialize(byte[] key)
        {
            X = 0;
            Y = 0;
            Z = 0;

            foreach (byte b in key)
            {
                for (int i = 0; i < 8; i++)
                {
                    int keyBit = (b >> i) & 1;
                    X = ((X << 1) | (uint)keyBit) & X_MASK;
                    Y = ((Y << 1) | (uint)keyBit) & Y_MASK;
                    Z = ((Z << 1) | (uint)keyBit) & Z_MASK;
                }
            }

            for (int i = 0; i < 100; i++)
                GetKeystreamBit();
        }

        private int Majority(int x, int y, int z)
        {
            return (x + y + z) >= 2 ? 1 : 0;
        }

        private int GetBit(uint reg, int pos)
        {
            return (int)((reg >> pos) & 1);
        }

        private void ClockX() => X = ((X << 1) | (uint)(GetBit(X, 13) ^ GetBit(X, 16) ^ GetBit(X, 17) ^ GetBit(X, 18))) & X_MASK;
        private void ClockY() => Y = ((Y << 1) | (uint)(GetBit(Y, 20) ^ GetBit(Y, 21))) & Y_MASK;
        private void ClockZ() => Z = ((Z << 1) | (uint)(GetBit(Z, 7) ^ GetBit(Z, 20) ^ GetBit(Z, 21) ^ GetBit(Z, 22))) & Z_MASK;

        private int GetKeystreamBit()
        {
            int m = Majority(GetBit(X, 8), GetBit(Y, 10), GetBit(Z, 10));
            if (GetBit(X, 8) == m) ClockX();
            if (GetBit(Y, 10) == m) ClockY();
            if (GetBit(Z, 10) == m) ClockZ();

            return GetBit(X, 18) ^ GetBit(Y, 21) ^ GetBit(Z, 22);
        }

        public void Process(byte[] data)
        {
            for (int i = 0; i < data.Length; i++)
            {
                byte output = 0;
                for (int bit = 0; bit < 8; bit++)
                {
                    int dataBit = (data[i] >> bit) & 1;
                    int ksBit = GetKeystreamBit();
                    int cipherBit = dataBit ^ ksBit;
                    output |= (byte)(cipherBit << bit);
                }
                data[i] = output;
            }
        }
    }
}
