using GRPCCommon.Protobuf.Common;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using UIAutomation.Exceptions;

namespace UIAutomation.BrowserExtensions
{
    /// <summary>
    /// 扩展管理
    /// </summary>
    public class ExtensionManager
    {
        private readonly IServiceProvider serviceProvider;
        private readonly ILogger<ExtensionManager> logger;

        public ExtensionManager(IServiceProvider serviceProvider, ILogger<ExtensionManager> logger)
        {
            this.serviceProvider = serviceProvider;
            this.logger = logger;
        }

        internal IEnumerable<BrowserExtension> GetExtensions()
        {
            //IEnumerable<BrowserExtension> extensions = this.serviceProvider.GetServices<BrowserExtension>();
            return this.serviceProvider.GetServices<BrowserExtension>();
        }

        /// <summary>
        /// 获取浏览器对应的插件类型
        /// </summary>
        /// <param name="browserType"></param>
        /// <returns></returns>
        internal BrowserExtension GetBrowserExtension(BrowserType browserType)
        {
            foreach (BrowserExtension browserExtension in this.GetExtensions())
            {
                switch (browserType)
                {
                    case BrowserType.Chrome:
                        if (browserExtension is ChromeExtension)
                            return browserExtension;
                        break;
                    case BrowserType.Firefox:
                        if (browserExtension is FirefoxExtension)
                            return browserExtension;
                        break;
                    case BrowserType.Edge:
                        if (browserExtension is EdgeExtension)
                            return browserExtension;
                        break;
                }
            }
            throw new BrowserExtensionException("不支持的浏览器插件");
        }
    }
}
