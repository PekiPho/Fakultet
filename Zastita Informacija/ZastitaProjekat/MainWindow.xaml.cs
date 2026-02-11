using System;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using ZastitaProjekat.Services;

namespace ZastitaProjekat
{
    public partial class MainWindow : Window
    {
        private readonly LogService logService;
        private readonly FileService fileService;
        private readonly WatcherService watcherService;
        private readonly NetworkService networkService;

        private bool isFSWActive = false;
        private bool isServerRunning = false;

        public MainWindow()
        {
            InitializeComponent();

            logService = new LogService();
            fileService = new FileService(logService);
            watcherService = new WatcherService(logService, fileService);

            networkService = new NetworkService(logService, fileService);

            DataContext = logService;
            logService.Log("Sys", "Aplikacija pokrenuta");
        }

        private byte[] StringToByteArray(string hex)
        {
            try
            {
                if (string.IsNullOrEmpty(hex)) return null;
                return Enumerable.Range(0, hex.Length)
                                    .Where(x => x % 2 == 0)
                                    .Select(x => Convert.ToByte(hex.Substring(x, 2), 16))
                                    .ToArray();
            }
            catch
            {
                return null;
            }
        }

        private void BtnBrowse_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new System.Windows.Forms.FolderBrowserDialog();
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                TxtFolderPath.Text = dialog.SelectedPath;
            }
        }

        private void BtnToggleFSW_Click(object sender, RoutedEventArgs e)
        {
            if (!isFSWActive)
            {
                byte[] key = StringToByteArray(TxtKey.Text);
                byte[] iv = StringToByteArray(TxtIV.Text);

                if (key == null || iv == null || string.IsNullOrEmpty(TxtFolderPath.Text))
                {
                    System.Windows.MessageBox.Show("Unesite ispravan kljuc, IV i putanju foldera!");
                    return;
                }

                watcherService.CurrentKey = key;
                watcherService.CurrentIV = iv;
                watcherService.CurrentAlgo = (ComboAlgo.SelectedItem as System.Windows.Controls.ComboBoxItem).Content.ToString();

                watcherService.Start(TxtFolderPath.Text);

                BtnToggleFSW.Content = "Zaustavi FSW";
                BtnToggleFSW.Background = System.Windows.Media.Brushes.Tomato;
                isFSWActive = true;
            }
            else
            {
                watcherService.Stop();
                BtnToggleFSW.Content = "Ukljuci FSW";
                BtnToggleFSW.Background = System.Windows.Media.Brushes.LightGreen;
                isFSWActive = false;
            }
        }

        private void BtnStartServer_Click(object sender, RoutedEventArgs eventArgs)
        {
            if (!isServerRunning)
            {
                byte[] key = StringToByteArray(TxtKey.Text);
                if (key == null)
                {
                    System.Windows.MessageBox.Show("Unesite ispravan ključ (HEX) pre pokretanja servera!");
                    return;
                }

                isServerRunning = true;
                BtnStartServer.Content = "Zaustavi Server";
                BtnStartServer.Background = System.Windows.Media.Brushes.Tomato;

                string outputDir = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Output");

                Task.Run(async () => await networkService.StartReceiving(outputDir, key));
            }
            else
            {
                networkService.StopReceiving();
                BtnStartServer.Content = "Pokreni Server - Listen";
                BtnStartServer.Background = System.Windows.Media.Brushes.LightBlue;
                isServerRunning = false;
            }
        }

        private async void BtnSend_Click(object sender, RoutedEventArgs eventArgs)
        {
            //Blake2sTest.Run();
            //Blake2sTest.RunXTEA();

            Microsoft.Win32.OpenFileDialog ofd = new Microsoft.Win32.OpenFileDialog();
            ofd.Filter = "Protected files (*.protected)|*.protected|All files (*.*)|*.*";

            if (ofd.ShowDialog() == true)
            {
                byte[] key = StringToByteArray(TxtKey.Text);
                string algo = (ComboAlgo.SelectedItem as System.Windows.Controls.ComboBoxItem).Content.ToString();

                await networkService.SendFile(TxtIP.Text, ofd.FileName, key, algo);
            }


        }
    }
}