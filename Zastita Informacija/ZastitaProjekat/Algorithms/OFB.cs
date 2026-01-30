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
            this.inV = (uint[])inV.Clone();
            buffIndex = 8;
        }

        public void Process(byte[] data)
        {
            for(int i = 0; i < data.Length; i++)
            {
                if(buffIndex == 8)
                {
                    XTEA.Encrypt(inV, this.key);

                    Buffer.BlockCopy(inV, 0, keystreamBuff, 0, 8);

                    buffIndex = 0;
                }

                data[i] ^= keystreamBuff[buffIndex++];
            }
        }
    }
}
