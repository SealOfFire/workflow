// -------------------------------------------------
// 和web浏览器插件通信的exe
//
// -------------------------------------------------
using Grpc.Core;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.DependencyInjection.Extensions;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using NativeMessageHost.Handles;
using NLog;
using NLog.Extensions.Logging;

namespace NativeMessageHost
{
    internal class Program
    {
        /// <summary>
        /// 依赖注入的配置
        /// </summary>
        /// <param name="services"></param>
        private static void ConfigureServices(IServiceCollection services)
        {
            var configuration = new ConfigurationBuilder()
                 .SetBasePath(System.IO.Directory.GetCurrentDirectory()) //From NuGet Package Microsoft.Extensions.Configuration.Json
                 .AddJsonFile("appsettings.json", optional: true, reloadOnChange: true)
            .Build();

            services.Configure<Options>(configuration.GetSection("NativeMessageHost"));

            services.AddLogging(
                loggingBuilder =>
                {
                    // configure Logging with NLog
                    loggingBuilder.ClearProviders();
                    loggingBuilder.SetMinimumLevel(Microsoft.Extensions.Logging.LogLevel.Trace);
                    loggingBuilder.AddNLog(configuration);
                });

            // 后台队列
            //services.AddSingleton<MonitorLoop>();
            //services.TryAddSingleton<ConsoleProcessMessage>();
            services.TryAddSingleton<JsonDictionary>();
            services.TryAddSingleton<ConsoleBackgroundTask>();
            services.TryAddSingleton<NamedPipeBackgroundTask>();
            // Grpc服务注入
            //services.TryAddScoped<UIAutomation>();
            services.TryAddScoped<NativeMessageService>();
            services.TryAddSingleton<GrpcService>();
            //services.TryAddSingleton<ConsoleBackgroundService>();
            //services.TryAddSingleton<NamedPipeBackgroundService>();
            // 后台服务
            services.AddHostedService<ConsoleBackgroundService>();
            services.AddHostedService<NamedPipeBackgroundService>();


            //services.AddGrpc();

            //services.AddHostedService<QueuedHostedService>();
            //services.AddSingleton<IBackgroundTaskQueue>(_ =>
            //{
            //    return new DefaultBackgroundTaskQueue(20);
            //});
            //services.AddSingleton<IBackgroundMessageQueue>(_ =>
            //{
            //    return new DefaultBackgroundMessageQueue(20);
            //});

            services.AddHandles(); // 通过反射自动注入handls下面继承自BaseHandle的类
            services.TryAddSingleton<HandleManager>();
        }

        /// <summary>
        /// 程序退出前需要做的处理
        /// </summary>
        private static void BeforeExit()
        {
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="args"></param>
        [STAThread]
        public static async Task Main(string[] args)
        {
            Logger logger = LogManager.GetCurrentClassLogger();

            //logger.Info("started1");
            ////var exitEvent = new ManualResetEvent(false);
            //Console.CancelKeyPress +=(sender, eventArgs) =>
            //{
            //    logger.Info("stopped1");
            //};

            //AppDomain.CurrentDomain.ProcessExit += (sender, e) =>
            //{
            //    logger.Info("stopped2");
            //};

            //AssemblyLoadContext.Default.Unloading += ctx =>
            //{
            //    logger.Info("stopped3");
            //};

            //await Host.CreateDefaultBuilder(args).ConfigureServices((context, services) =>
            //{
            //    ConfigureServices(services);
            //}).RunConsoleAsync();

            IHost? host = Host.CreateDefaultBuilder()
                  .ConfigureServices((context, services) =>
                  {
                      ConfigureServices(services);
                  })
                  .UseConsoleLifetime(opts => { opts.SuppressStatusMessages = true; })
            .Build();

            ////exitEvent.WaitOne();
            //logger.Info("started2");

            IOptions<Options> options = host.Services.GetRequiredService<IOptions<Options>>();
            //IHostApplicationLifetime appLifttime = host.Services.GetRequiredService<IHostApplicationLifetime>();
            //appLifttime.ApplicationStarted.Register(() => { logger.Info("started"); });
            //appLifttime.ApplicationStopping.Register(() => { logger.Info("stoping"); });
            //appLifttime.ApplicationStopped.Register(() => { logger.Info("stopped"); });

            string processName = options.Value.PipeName;

            bool isRuned;
            Mutex mutex = new Mutex(true, processName, out isRuned);
            if (isRuned)
            {
                try
                {
                    logger.Info("NativeMessageHost 启动");
                    foreach (string arg in args)
                    {
                        logger.Info($"args:{arg}");
                    }

                    // 启动grpc服务
                    var server = host.Services.GetRequiredService<GrpcService>();
                    server.Start();
                    logger.Trace("grpc服务 -- 启动");

                    //host.RegisterApplicationLifetimeEvents();
                    host.Run();

                    logger.Info("程序运行结束");
                }
                catch (Exception ex)
                {
                    logger.Error(ex);
                    throw;
                }
                finally
                {
                    mutex.ReleaseMutex();
                }
            }
            else
            {
                logger.Warn("重复启动");
            }
        }

    }
}

// //https://stackoverflow.com/questions/48746426/implement-websocket-in-chrome-extension
// https://learn.microsoft.com/zh-cn/dotnet/csharp/asynchronous-programming/start-multiple-async-tasks-and-process-them-as-they-complete