using Microsoft.Extensions.Logging;
using ProcessCommunication;
using System.IO.Pipes;

namespace UIAutomation.BrowserExtensions
{
    /// <summary>
    /// 和插件服务通信的客户端
    /// todo 单元测试结结束后改为 internal
    /// </summary>
    public class NativeMessageClient
    {
        private readonly ILogger<NativeMessageClient> logger;
        private NamedPipeClientStream? namedPipeClientStream;

        public NativeMessageClient(ILogger<NativeMessageClient> logger)
        {
            this.logger = logger;
        }

        public void Connect(string pipeName)
        {
            Console.WriteLine("连接到服务器");
            this.namedPipeClientStream = new NamedPipeClientStream(".", pipeName, PipeDirection.InOut);
            if (!this.namedPipeClientStream.IsConnected)
            {
                this.namedPipeClientStream?.Connect();
            }
            Console.WriteLine("连接成功");
        }

        public void Close()
        {
            this.namedPipeClientStream?.Close();
        }

        /// <summary>
        /// 单线程执行，会在这里等待服务器的回复
        /// </summary>
        /// <param name="processMessage"></param>
        public ProcessMessage Send(string pipeName, ProcessMessage processMessage)
        {
            //this.namedPipeClientStream.Connect();
            if (this.namedPipeClientStream !=null)
            {
                GRPCCommon.GRPCCommonTools.Send(this.namedPipeClientStream, processMessage);

                // 等待回复
                Console.WriteLine("等待服务器发送的数据");

                ProcessMessage? result = GRPCCommon.GRPCCommonTools.Read2(this.namedPipeClientStream);
                Console.WriteLine("服务器数据传入成功");

                return result;
            }
            else
            {
                throw new ArgumentNullException("NamedPipeClientStream");
            }
            //// 这里会无线循环
            //Thread.Sleep(2000);
            //this.Send(processMessage);
        }


        public GRPCCommon.Response Send(string pipeName, GRPCCommon.Request request)
        {
            //this.namedPipeClientStream.Connect();
            if (this.namedPipeClientStream !=null)
            {
                GRPCCommon.GRPCCommonTools.Send(this.namedPipeClientStream, request);

                // 等待回复
                Console.WriteLine("等待服务器发送的数据");

                GRPCCommon.Response? result = GRPCCommon.GRPCCommonTools.Read(this.namedPipeClientStream);
                Console.WriteLine("服务器数据传入成功");

                return result;
            }
            else
            {
                throw new ArgumentNullException("NamedPipeClientStream");
            }
            //// 这里会无线循环
            //Thread.Sleep(2000);
            //this.Send(processMessage);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="processMessage"></param>
        /// <returns></returns>
        public ProcessMessage? Send(ProcessMessage processMessage)
        {
            this.Write(processMessage);
            ProcessMessage? result = this.Read2();
            return result;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="processMessage"></param>
        /// <returns></returns>
        public GRPCCommon.Response? Send(GRPCCommon.Request request)
        {
            this.Write(request);
            GRPCCommon.Response? result = this.Read();
            return result;
        }

        public ProcessMessage? Read2()
        {
            if (this.namedPipeClientStream !=null)
            {
                ProcessMessage? processMessage = GRPCCommon.GRPCCommonTools.Read2(this.namedPipeClientStream);
                if (processMessage == null)
                {
                    this.logger.LogError("从管道读取数据出错");
                    return null;
                }
                else
                {
                    return processMessage;
                }
            }
            else
            {
                this.logger.LogError("没有管道");
                return null;
            }
        }

        public GRPCCommon.Response? Read()
        {
            if (this.namedPipeClientStream !=null)
            {
                GRPCCommon.Response? response = GRPCCommon.GRPCCommonTools.Read(this.namedPipeClientStream);
                if (response == null)
                {
                    this.logger.LogError("从管道读取数据出错");
                    return null;
                }
                else
                {
                    return response;
                }
            }
            else
            {
                this.logger.LogError("没有管道");
                return null;
            }
        }

        public void Write(ProcessMessage processMessage)
        {
            if (this.namedPipeClientStream !=null)
            {
                if (!this.namedPipeClientStream.IsConnected)
                {
                    this.namedPipeClientStream.Connect();
                }
                byte[] buffer = GRPCCommon.GRPCCommonTools.ToBytes(processMessage);
                this.namedPipeClientStream.Write(buffer, 0, buffer.Length);
                this.namedPipeClientStream.Flush();

                //byte[] lengthBuffer = new byte[4];
                //this.namedPipeClientStream.Read(lengthBuffer, 0, lengthBuffer.Length);
                //int debug = 0;
                //debug++;
            }
            else
            {
                this.logger.LogError("没有管道");
            }
        }

        public void Write(GRPCCommon.Request request)
        {
            if (this.namedPipeClientStream !=null)
            {
                if (!this.namedPipeClientStream.IsConnected)
                {
                    this.namedPipeClientStream.Connect();
                }
                byte[] buffer = GRPCCommon.GRPCCommonTools.ToBytes(request);
                this.namedPipeClientStream.Write(buffer, 0, buffer.Length);
                this.namedPipeClientStream.Flush();

                //byte[] lengthBuffer = new byte[4];
                //this.namedPipeClientStream.Read(lengthBuffer, 0, lengthBuffer.Length);
                //int debug = 0;
                //debug++;
            }
            else
            {
                this.logger.LogError("没有管道");
            }
        }

    }
}
