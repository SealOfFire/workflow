using FlaUI.Core.AutomationElements;
using FlaUI.Core.Exceptions;
using Microsoft.Extensions.Logging;

namespace UIAutomation.BrowserExtensions
{
    internal class FirefoxExtension : BrowserExtension
    {
        private const string PIPE_NAME = "NativeMessageHost";

        public FirefoxExtension(ILogger<FirefoxExtension> logger,
            NativeMessageClient nativeMessageClient,
            GrpcNativeMessageClient grpcNativeMessageClient)
            : base(logger, nativeMessageClient, grpcNativeMessageClient)
        {
            // TODO 修改配置
            this.grpcNativeMessageClient.Connect(50001);
        }

        internal override bool InBrowserDocument(AutomationElement automationElement, out AutomationElement? document)
        {
            document=null;
            return false;
        }
    }
}
