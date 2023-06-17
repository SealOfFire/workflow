using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Text;

namespace NativeMessageHost
{
    internal class ConsoleBackgroundTask
    {
        private readonly ILogger<ConsoleBackgroundTask> logger;
        //private readonly IHostApplicationLifetime appLifetime;
        //private readonly IBackgroundMessageQueue backgroundMessageQueue;
        //private readonly ConsoleProcessMessage consoleProcessMessage;
        private readonly JsonDictionary jsonDictionary;

        public ConsoleBackgroundTask(ILogger<ConsoleBackgroundTask> logger,
            //IHostApplicationLifetime appLifetime,
            //ConsoleProcessMessage consoleProcessMessage,
            JsonDictionary jsonDictionary
            /*IBackgroundMessageQueue backgroundMessageQueue*/)
        {
            this.logger = logger;
            //this.consoleProcessMessage = consoleProcessMessage;
            //this.backgroundMessageQueue=backgroundMessageQueue;
            this.jsonDictionary = jsonDictionary;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="stoppingToken"></param>
        /// <returns></returns>
        public async Task ReadAsync(CancellationToken stoppingToken)
        {
            try
            {
                using (Stream stream = Console.OpenStandardInput())
                {
                    while (!stoppingToken.IsCancellationRequested)
                    {
                        //this.logger.LogInformation($"控制台后台服务等待数据读取");
                        byte[] lengthBuffer = new byte[4];
                        await stream.ReadAsync(lengthBuffer, 0, lengthBuffer.Length)
                            .ContinueWith(async t =>
                            {
                                if (t.Result>0)
                                {
                                    int length = BitConverter.ToInt32(lengthBuffer, 0);
                                    this.logger.LogInformation($"控制台后台服务读取到数据长度:[{length}]");
                                    byte[] dataBuffer = new byte[length];
                                    await stream.ReadAsync(dataBuffer, 0, length);
                                    string text = Encoding.UTF8.GetString(dataBuffer);
                                    this.logger.LogInformation($"控制台后台服务读取到数据:[{text}]");

                                    //ExpandoObject? result = System.Text.Json.JsonSerializer.Deserialize<ExpandoObject>(text);
                                    //dynamic? result = JsonConvert.DeserializeObject(text);
                                    //ProcessMessage? result = System.Text.Json.JsonSerializer.Deserialize<ProcessMessage>(text);
                                    //ProcessMessage? result = System.Text.Json.JsonSerializer.Deserialize<ProcessMessage>(text);
                                    //ProcessMessage? result = JsonConvert.DeserializeObject<ProcessMessage>(text);
                                    JObject? jobject = JsonConvert.DeserializeObject<JObject>(text);
                                    //Message message = new Message { Direction= MessageDirection.ConsoleToPip, Data=result };
                                    //await this.backgroundMessageQueue.QueueBackgroundWorkItemAsync(message);
                                    if (jobject !=null)
                                    {
                                        string id = jobject.GetValue("Id").Value<string>();
                                        //string id = ((IDictionary<string, object>)result)["Id"].ToString();
                                        if (this.jsonDictionary.ContainsKey(id))
                                        {
                                            // 消息id重复
                                            this.logger.LogError("控制台后台服务读取到的id重复");
                                        }
                                        else
                                        {
                                            //this.consoleProcessMessage.Add(result.Id, result);
                                            this.jsonDictionary.Add(id, jobject);

                                            //this.consoleProcessMessage.Add(id, new ExpandoObject());
                                            //int debug = 0;
                                            //debug++;
                                        }
                                    }
                                }
                                else
                                {
                                    this.logger.LogInformation($"控制台后台服务读取到关闭程序");
                                    //this.appLifetime.StopApplication();
                                    //stoppingToken.ThrowIfCancellationRequested();
                                    Environment.Exit(0);
                                    //Message message = new Message { Direction= MessageDirection.Exit, Data = new ProcessMessage() };
                                    //await this.backgroundMessageQueue.QueueBackgroundWorkItemAsync(message);
                                    //throw new Exception("关闭程序");
                                    //Thread.Sleep(2000);
                                }
                            });
                    }
                }
            }
            catch (OperationCanceledException)
            {
                // Prevent throwing if stoppingToken was signaled
            }
            catch (Exception ex)
            {
                this.logger.LogError(ex, "控制台后台服务出错");
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="data"></param>
        public void Write(byte[] data)
        {
            this.logger.LogDebug($"控制台后台服务写数据");
            using (Stream stream = Console.OpenStandardOutput())
            {
                stream.Write(data, 0, data.Length);
            }
        }
    }
}
