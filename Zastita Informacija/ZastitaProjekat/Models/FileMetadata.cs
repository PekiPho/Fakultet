using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZastitaProjekat.Models
{
    public class FileMetadata
    {

        public string FileName { get; set; }
        public long FileSize { get; set; }

        public DateTime CreationTime { get; set; }

        public string EncryptionAlgo { get; set; }

        public string HashAlgo { get; set; }

        public byte[] HashValue { get; set; }

        public byte[] IV { get; set; }


    }
}
