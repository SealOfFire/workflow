using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using System.IO.Pipes;

namespace NativeMessageHost
{
    internal class NamedPipeBackgroundService : BackgroundService
    {
        private readonly ILogger<NamedPipeBackgroundService> logger;
        private readonly NamedPipeBackgroundTask task;

        /// <summary>
        /// 
        /// </summary>
        private NamedPipeServerStream? pipeServerStream;

        /// <summary>
        /// 构造函数
        /// </summary>
        public NamedPipeBackgroundService(
            ILogger<NamedPipeBackgroundService> logger,
            NamedPipeBackgroundTask task)
            => (this.logger, this.task) = (logger, task);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="stoppingToken"></param>
        /// <returns></returns>
        protected override Task ExecuteAsync(CancellationToken stoppingToken)
        {
            this.logger.LogInformation("管道后台服务启动");

            this.task.ReadAndWrite();
            return Task.CompletedTask;
            //return this.task.ReadAsync(stoppingToken);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="stoppingToken"></param>
        /// <returns></returns>
        public override async Task StopAsync(CancellationToken stoppingToken)
        {
            this.logger.LogInformation($"管道后台服务停止");

            await base.StopAsync(stoppingToken);
        }

    }
}
