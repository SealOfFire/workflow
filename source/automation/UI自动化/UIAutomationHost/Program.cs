// -------------------------------------------------
// UI自动化 主程序
//
// -------------------------------------------------
// See https://aka.ms/new-console-template for more information
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.DependencyInjection.Extensions;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using NLog;
using NLog.Extensions.Logging;
using UIAutomation.BrowserExtensions;
using UIAutomationHost;

internal class Program
{

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

        services.TryAddSingleton<NativeMessageClient>();
    }

    static public async Task Main(string[] args)
    {
        Logger logger = LogManager.GetCurrentClassLogger();
        logger.Info("UIAutomationHost 启动");
        foreach (string arg in args)
        {
            logger.Info($"args:{arg}");
        }

        IHost? host = Microsoft.Extensions.Hosting.Host.CreateDefaultBuilder()
        .ConfigureServices((context, services) =>
        {
            ConfigureServices(services);
        })
        .Build();

        await host!.StartAsync();

        logger.Info("UIAutomationHost 程序运行结束");
    }
}