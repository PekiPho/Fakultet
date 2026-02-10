using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace ZastitaProjekat.Algorithms
{
    public class OFB
    {
        private uint[] key;
        private uint[] inV;
        private byte[] keystreamBuff = new byte[8];
        private int buffIndex = 8;

        public void Initialize(uint[] key, uint[] iv)
        {
            if (key.Length != 4) throw new ArgumentException("XTEA kljuc mora da bude 128b");
            if (iv.Length != 2) throw new ArgumentException("Inicijalizacioni vektor mora da bude 64b");

            this.key=(uint[])key.Clone();
            this.inV = (uint[])iv.Clone();
            buffIndex = 8;
        }

        public void Process(byte[] data)
        {
            for(int i = 0; i < data.Length; i++)
            {
                if(buffIndex == 8)
                {
                    XTEA.Encrypt(inV, this.key);

                    keystreamBuff[0] = (byte)(inV[0] & 0xFF);
                    keystreamBuff[1] = (byte)((inV[0] >> 8) & 0xFF);
                    keystreamBuff[2] = (byte)((inV[0] >> 16) & 0xFF);
                    keystreamBuff[3] = (byte)((inV[0] >> 24) & 0xFF);

                    keystreamBuff[4] = (byte)(inV[1] & 0xFF);
                    keystreamBuff[5] = (byte)((inV[1] >> 8) & 0xFF);
                    keystreamBuff[6] = (byte)((inV[1] >> 16) & 0xFF);
                    keystreamBuff[7] = (byte)((inV[1] >> 24) & 0xFF);

                    buffIndex = 0;
                }

                data[i] ^= keystreamBuff[buffIndex++];
            }
        }

    }
}
