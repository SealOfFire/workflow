using FlaUI.UIA2;
using FlaUI.UIA3;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.DependencyInjection.Extensions;
using UIAutomation.BrowserExtensions;
using UIAutomation.Managers;

namespace UIAutomation
{
    public static class ServiceCollectionExtensions
    {
        public static IServiceCollection AddUIAutomation(this IServiceCollection services)
        {
            services.TryAddSingleton<Selector>();
            services.TryAddSingleton<GrpcManager>(); // TODO 通过grpc调用很慢
            services.TryAddSingleton<ApiManager>();
            services.TryAddSingleton<UIManager>();
            services.TryAddSingleton<UIA2Automation>();
            services.TryAddSingleton<UIA3Automation>();
            //services.TryAddSingleton<ExtensionCollection>();
            services.TryAddSingleton<UIAutomation>();
            services.TryAddSingleton<NativeMessageClient>();

            // 每个插件内有自己的客户端，这个不使用单例
            //services.TryAddScoped<GrpcNativeMessageClient>();
            services.TryAddTransient<GrpcNativeMessageClient>();

            // 处理浏览插件的类
            services.TryAddSingleton<ExtensionManager>();
            services.TryAddSingleton<BrowserExtension, ChromeExtension>();
            services.TryAddSingleton<BrowserExtension, EdgeExtension>();
            services.TryAddSingleton<BrowserExtension, FirefoxExtension>();

            return services;
        }
    }
}
