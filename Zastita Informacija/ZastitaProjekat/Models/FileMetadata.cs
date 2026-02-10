using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace ZastitaProjekat.Models
{
    public class FileMetadata
    {
        [JsonPropertyName("FileName")]
        public string FileName { get; set; }

        [JsonPropertyName("FileSize")]
        public long FileSize { get; set; }


        [JsonPropertyName("CreatedAt")]
        public DateTime CreationTime { get; set; }

        [JsonPropertyName("EncryptionAlgorithm")]
        public string EncryptionAlgo { get; set; }

        [JsonPropertyName("HashAlgorithm")]
        public string HashAlgo { get; set; }

        [JsonPropertyName("HashValue")]
        public byte[] HashValue { get; set; }

        [JsonPropertyName("IV")]
        public byte[] IV { get; set; }

        [JsonPropertyName("CipherMode")]
        public string CipherMode { get; set; }

    }
}
