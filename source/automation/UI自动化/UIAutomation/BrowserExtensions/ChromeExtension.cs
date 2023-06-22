using FlaUI.Core.AutomationElements;
using FlaUI.Core.Exceptions;
using Microsoft.Extensions.Logging;

namespace UIAutomation.BrowserExtensions
{
    internal class ChromeExtension : BrowserExtension
    {
        private const string PIPE_NAME = "NativeMessageHost";

        public ChromeExtension(ILogger<ChromeExtension> logger,
            NativeMessageClient nativeMessageClient,
            GrpcNativeMessageClient grpcNativeMessageClient)
            : base(logger, nativeMessageClient, grpcNativeMessageClient)
        {
            // TODO 修改配置
            this.grpcNativeMessageClient.Connect(50001);
        }

        internal override bool InBrowserDocument(AutomationElement automationElement, out AutomationElement? document)
        {
            // 向上查看父级是否在浏览器中。如果鼠标是浏览器中的html元素，向上一直找到浏览器的根。
            // 如果选中的是浏览器的html容器，没法再进去了，同样通过查看父级获取是否在浏览器中
            bool inDocument = false;
            document = null;
            if (automationElement.Parent !=null)
            {
                AutomationElement parent = automationElement.Parent;
                while (true)
                {
                    try
                    {
                        if (parent.ControlType == FlaUI.Core.Definitions.ControlType.Document)
                        {
                            // 鼠标在文档部分
                            inDocument = true;
                            document = parent;
                        }
                        if (parent.ClassName=="Chrome_WidgetWin_1"
                            && parent.ControlType == FlaUI.Core.Definitions.ControlType.Pane)
                        {
                            // chrome浏览器
                            return true && inDocument;
                        }
                        else
                        {
                            if (parent.Parent !=null)
                                parent = parent.Parent;
                            else
                                return false;
                        }
                    }
                    catch (PropertyNotSupportedException)
                    {
                        if (parent.Parent !=null)
                            parent = parent.Parent;
                        else
                            return false;
                    }
                }
            }

            return false;
        }
    }
}
