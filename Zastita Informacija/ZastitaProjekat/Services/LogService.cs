using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using ZastitaProjekat.Models;

namespace ZastitaProjekat.Services
{
    public class LogService
    {

        private const string LogFilePath = "logs.txt";

        public ObservableCollection<LogEntry> Logs { get; } = new ObservableCollection<LogEntry>();

        public LogService()
        {
            File.WriteAllText(LogFilePath, string.Empty);
        }
        public void Log(string action, string details, string status = "Success")
        {
            var entry = new LogEntry
            {
                Timestamp = DateTime.Now,
                Action = action,
                Details = details,
                Status = status
            };

            App.Current.Dispatcher.Invoke(() => Logs.Insert(0, entry));

            string logLine = $"[{entry.Timestamp:yyyy-MM-dd HH:mm:ss}] {action} | {status} | {details}";
            File.AppendAllLines(LogFilePath, new[] { logLine });
        }
    }
}
