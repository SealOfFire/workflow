using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.DependencyInjection.Extensions;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using NLog;
using NLog.Extensions.Logging;
using System.Drawing;
using UIAutomation;
using UIAutomation.Managers;

namespace UIAutomationServer
{

    internal class Program
    {
        private static void ConfigureServices(IServiceCollection services)
        {
            var configuration = new ConfigurationBuilder()
                 .SetBasePath(System.IO.Directory.GetCurrentDirectory()) //From NuGet Package Microsoft.Extensions.Configuration.Json
                 .AddJsonFile("appsettings.json", optional: true, reloadOnChange: true)
            .Build();

            services.Configure<Options>(configuration.GetSection("ElementSelectorOptions"));

            services.AddLogging(
                loggingBuilder =>
                {
                    // configure Logging with NLog
                    loggingBuilder.ClearProviders();
                    loggingBuilder.SetMinimumLevel(Microsoft.Extensions.Logging.LogLevel.Trace);
                    loggingBuilder.AddNLog(configuration);
                }
                );

            services.TryAddScoped<UIASelectorService>();

            // flaUI
            services.AddUIAutomation();

            // grpc服务
            services.TryAddSingleton<Server>();
        }

        [STAThread]
        static async Task Main(string[] args)
        {
            Logger logger = LogManager.GetCurrentClassLogger();

            IHost? host = Microsoft.Extensions.Hosting.Host.CreateDefaultBuilder()
            .ConfigureServices((context, services) =>
            {
                ConfigureServices(services);
            })
            .Build();

            await host!.StartAsync();

            // 启动grpc服务
            var server = host.Services.GetRequiredService<Server>();
            server.Start();
            logger.Trace("元素识别GRPC服务 -- 启动");


            //Form1 form1 = new Form1();
            //form1.Show();

            //int debug = 0;
            //AutomationType automationType = AutomationType.UIA2;

            //AutomationBase automation = automationType == AutomationType.UIA2 ? (AutomationBase)new UIA2Automation() : new UIA3Automation();
            //AutomationElement rootElement = automation.GetDesktop();


            //string aa1 = "FlaUITest (正在调试) - Microsoft Visual Studio";
            //string aa2 = "FlaUITest (正在运行) - Microsoft Visual Studio";
            //PropertyCondition propertyCondition1 = new PropertyCondition(automation.PropertyLibrary.Element.Name, aa1);

            //var found1 = rootElement.FindAllChildren();
            //var found2 = rootElement.FindAll(TreeScope.Children, propertyCondition1);


            Console.WriteLine("press any key to exit");
            string? aa = Console.ReadLine();
            if (aa != null)
            {
                var elementManager = host.Services.GetRequiredService<GrpcManager>();
                System.Drawing.Color color = Color.Red;
                TimeSpan duration = TimeSpan.FromMilliseconds(2);
                elementManager.Highlight(new Element(), color, duration, UIAType.Uia2);
            }

            host?.StopAsync();

        }
    }

}