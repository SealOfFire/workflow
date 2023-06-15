using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace NativeMessageHost
{
    internal class ConsoleBackgroundService : BackgroundService
    {
        private readonly ILogger<ConsoleBackgroundService> logger;
        //private readonly IHostApplicationLifetime appLifetime;
        private readonly ConsoleBackgroundTask task;

        /// <summary>
        /// 构造函数
        /// </summary>
        public ConsoleBackgroundService(
            ILogger<ConsoleBackgroundService> logger,
            //IHostApplicationLifetime appLifetime,
            ConsoleBackgroundTask task)
        {
            this.logger = logger;
            //this.appLifetime = appLifetime;
            this.task = task;
        }

        public override Task StartAsync(CancellationToken cancellationToken)
        {
            return base.StartAsync(cancellationToken);
        }

        protected override Task ExecuteAsync(CancellationToken stoppingToken)
        {
            this.logger.LogInformation("控制台后台服务启动");

            return this.task.ReadAsync(stoppingToken);
            //return this.ReadAsync(stoppingToken);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="stoppingToken"></param>
        /// <returns></returns>
        public override async Task StopAsync(CancellationToken stoppingToken)
        {
            this.logger.LogInformation($"控制台后台服务停止");

            await base.StopAsync(stoppingToken);
        }

    }
}
