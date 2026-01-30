using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZastitaProjekat.Models
{
    public class LogEntry
    {
        public DateTime Timestamp { get; set; }
        public string Action { get; set; }
        public string Details { get; set; }
        public string Status { get; set; }
    }
}
