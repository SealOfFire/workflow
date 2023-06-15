using System;
using System.Diagnostics;
using System.Text;
using UIAutomation.BrowserExtensions;

namespace TestUIAutomation
{
    public class UnitTest2
    {
        public UnitTest2()
        {
        }

        [Fact]
        public void Test1()
        {
            ProcessStartInfo info = new ProcessStartInfo(@"D:\MyProgram\github\workflow\source\automation\UI自动化\NativeMessageHost\bin\Debug\net6.0\NativeMessageHost.exe")
            {
                RedirectStandardInput=true,
                RedirectStandardOutput=true,
                UseShellExecute=false,
            };
            //info.Arguments = @"/C ipconfig";//这样输入
            //info.UseShellExecute = false;
            //info.RedirectStandardOutput = true;
            Process p = new Process();
            p.StartInfo = info;
            p.Start();
            this.Write(p, "{\"aaa\":\"aaa\"}");
            this.Write(p, "{\"aaa\":\"bbb\"}");

            // 发送关闭命令代替kill
            p.StandardInput.Close();
            //p.Kill();
            p.WaitForExit();
            //MessageBox.Show(p.StandardOutput.ReadToEnd());
            //this.Write(p, "{\"aaa\":\"aaa\"}");
            int debug = 0;
            debug++;

        }

        private void Write(Process process, string text)
        {
            byte[] buffer = Encoding.UTF8.GetBytes(text);
            byte[] lengthBuffer = BitConverter.GetBytes(buffer.Length);

            char[] aaa = Encoding.UTF8.GetChars(buffer);
            char[] bbb = Encoding.UTF8.GetChars(lengthBuffer);

            //process.StandardInput.BaseStream.Write(lengthBuffer, 0, lengthBuffer.Length);
            //process.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            //char[] aa = (char[])buffer;

            process.StandardInput.Write(bbb);
            process.StandardInput.Write(aaa);
        }

    }
}