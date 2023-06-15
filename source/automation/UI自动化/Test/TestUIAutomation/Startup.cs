using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.DependencyInjection.Extensions;
using UIAutomation;
using UIAutomation.BrowserExtensions;

namespace TestUIAutomation
{
    public class Startup
    {
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddUIAutomation();

            services.TryAddSingleton<NativeMessageClient>();
            services.TryAddSingleton<GrpcNativeMessageClient>();

        }
    }
}
