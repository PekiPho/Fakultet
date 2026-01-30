using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZastitaProjekat.Services
{
    public class WatcherService
    {
        private FileSystemWatcher watcher;
        private readonly LogService logService;
        private readonly FileService fileService;


        public byte[] CurrentKey { get; set; }
        public byte[] CurrentIV { get; set; }
        public string CurrentAlgo { get; set; } = "XTEA";

        public WatcherService(LogService logService, FileService fileService)
        {
            this.logService = logService;
            this.fileService = fileService;
        }

        public void Start(string path)
        {
            if(!Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
            }

            watcher = new FileSystemWatcher(path);

            watcher.Created += OnChanged;
            watcher.Renamed += OnChanged;


            watcher.EnableRaisingEvents = true;

            logService.Log("FSW", $"Poceo pratiti folder: {path}");
        }

        public void Stop()
        {
            if(watcher != null )
            {
                watcher.EnableRaisingEvents = false;
                watcher.Dispose();

                logService.Log("FSW", "Prestao pratiti folder");
            }
        }


        public void OnChanged(object sender, FileSystemEventArgs e)
        {
            logService.Log("FSW Detekcija", $"Novi file kreiran: {e.Name}");


            Task.Run(async () =>
            {
                await Task.Delay(500);

                if (CurrentKey == null || CurrentIV == null)
                {
                    logService.Log("FSW Greska", "Kljuc ili IV nisu postavljeni!", "Fail");
                    return;
                }

                fileService.ProtectFile(e.FullPath, CurrentAlgo, CurrentKey, CurrentIV);
            });
        }
    }
}
