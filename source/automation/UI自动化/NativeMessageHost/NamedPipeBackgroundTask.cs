using Google.Protobuf;
using GRPCCommon.Protobuf.Common;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using NativeMessageHost.Handles;
using Newtonsoft.Json.Linq;
using System.IO.Pipes;

namespace NativeMessageHost
{
    internal class NamedPipeBackgroundTask
    {
        private readonly ILogger<NamedPipeBackgroundTask> logger;
        //private readonly IBackgroundMessageQueue backgroundMessageQueue;
        private readonly IOptions<Options> options;
        //private readonly ConsoleProcessMessage consoleProcessMessage;
        private readonly HandleManager handleManager;
        private readonly ConsoleBackgroundTask consoleBackgroundTask;
        private readonly JsonDictionary jsonDictionary;
        //
        private NamedPipeServerStream? pipeServerStream;

        public NamedPipeBackgroundTask(ILogger<NamedPipeBackgroundTask> logger,
            IOptions<Options> options,
            HandleManager handleManager,
            //ConsoleProcessMessage consoleProcessMessage,
            ConsoleBackgroundTask consoleBackgroundTask,
            JsonDictionary jsonDictionary
        /*IBackgroundMessageQueue backgroundMessageQueue*/)
        {
            this.logger = logger;
            this.options = options;
            //this.consoleProcessMessage = consoleProcessMessage;
            this.handleManager= handleManager;
            this.consoleBackgroundTask = consoleBackgroundTask;
            this.jsonDictionary = jsonDictionary;
            //this.backgroundMessageQueue=backgroundMessageQueue;
            //
            //this.pipeServerStream = new NamedPipeServerStream(options.Value.PipeName, PipeDirection.InOut);
        }

        #region 同步

        public void ReadAndWrite()
        {
            int interval = 0;

            while (true)
            {
                try
                {
                    this.logger.LogInformation("管道后台服务等待客户端连接");
                    this.pipeServerStream = new NamedPipeServerStream(options.Value.PipeName, PipeDirection.InOut);
                    this.pipeServerStream?.WaitForConnection();
                    //timer = DateTime.Now;
                    this.logger.LogInformation("管道后台服务客户端连接成功");

                    while (true)
                    {
                        if (this.pipeServerStream !=null)
                        {
                            if (!this.pipeServerStream.IsConnected)
                            {
                                // 连接关闭，重置管道
                                this.logger.LogWarning("连接关闭，重置管道");
                                throw new Exception("连接关闭，重置管道");
                            }

                            byte[] lengthBuffer = new byte[4];
                            int readLength = this.pipeServerStream.Read(lengthBuffer, 0, lengthBuffer.Length);

                            if (readLength>0)
                            {
                                interval=0; // 重置等待时间
                                int length = BitConverter.ToInt32(lengthBuffer, 0);
                                this.logger.LogInformation($"管道后台服务读取到数据长度:[{length}]");
                                byte[] dataBuffer = new byte[length];
                                readLength= this.pipeServerStream.Read(dataBuffer, 0, length);

                                //ProcessMessage processMessage = ProcessMessage.Parser.ParseFrom(dataBuffer);
                                Request request = Request.Parser.ParseFrom(dataBuffer);
                                if (string.IsNullOrEmpty(request.Id))
                                {
                                    request.Id = Guid.NewGuid().ToString();
                                }
                                if (request.MillisecondsTimeout==0)
                                {
                                    request.MillisecondsTimeout = 2000;
                                }
                                this.logger.LogInformation($"管道后台服务读取到数据内容:[{request}]");

                                // 数据发送到对应的处理程序
                                byte[] consoleBuffer = this.handleManager.ToConsole(request);
                                if (consoleBuffer.Length>0)
                                {
                                    this.consoleBackgroundTask.Write(consoleBuffer);

                                    // 遍历结果查看有没有符合要求的返回值
                                    //dynamic? result = null;
                                    JObject? result = null;
                                    bool isTimeout = Task.Run(() =>
                                    {
                                        while (this.jsonDictionary.ContainsKey(request.Id) == false) { }
                                        //result = this.consoleProcessMessage[request.Id];
                                        result = this.jsonDictionary[request.Id];
                                        //this.consoleProcessMessage.Remove(request.Id);
                                        this.jsonDictionary.Remove(request.Id);
                                    }).Wait(request.MillisecondsTimeout);
                                    //
                                    if (isTimeout)
                                    {
                                        // 回写回管道
                                        this.logger.LogWarning($"管道后台服务写入管道[{request}]");
                                        GRPCCommon.Protobuf.Common.Error? error;
                                        Response? response = this.handleManager.ToNamedPip<Response>(result, out error);
                                        if (response == null)
                                        {
                                            string message = $"管道后台服务转换json失败";
                                            this.logger.LogWarning(message);
                                            response = new Response();
                                            response.Error=new GRPCCommon.Protobuf.Common.Error { Message=message };
                                            this.Write(response);
                                        }
                                        else
                                        {
                                            response.Attribute.ElementType= GRPCCommon.Protobuf.Common.ElementType.Html;
                                            this.Write(response);
                                            this.logger.LogInformation($"管道后台服务写入管道完成");
                                        }
                                    }
                                    else
                                    {
                                        // 处理超时，返回错误信息 ProcessMessage
                                        string message = $"管道后台服务[{request.MillisecondsTimeout}]毫秒内，没有从控制台获取到返回的任务{request.Id},{request.Command}";
                                        this.logger.LogWarning(message);
                                        Response response = new();
                                        response.Error=new GRPCCommon.Protobuf.Common.Error { Message=message };
                                        this.Write(response);
                                    }
                                }
                                else
                                {
                                    string message = $"管道后台服务没有处理[{request.Command}]的方法";
                                    this.logger.LogWarning(message);
                                    Response response = new();
                                    response.Error=new GRPCCommon.Protobuf.Common.Error { Message=message };
                                    this.Write(response);
                                }
                            }
                            else
                            {
                                // 没读取到数据，逐步增加读取的等待间隔时间
                                interval = Math.Clamp(interval+5, 0, 2000);
                            }
                        }

                        Thread.Sleep(interval);
                    }

                }
                catch (Exception ex)
                {
                    this.logger.LogError(ex, "管道后台服务出错");
                    this.pipeServerStream?.Dispose();
                    //throw;
                }
            }
        }

        private void Write(Response response)
        {
            byte[] buffer = response.ToByteArray();
            byte[] lengthBuffer = BitConverter.GetBytes(buffer.Length);

            byte[] data = new byte[buffer.Length+lengthBuffer.Length];
            lengthBuffer.CopyTo(data, 0);
            buffer.CopyTo(data, lengthBuffer.Length);
            this.pipeServerStream?.Write(data);
            this.pipeServerStream?.Flush();
        }

        #endregion

    }
}
