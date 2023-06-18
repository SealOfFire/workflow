using FlaUI.Core;
using FlaUI.Core.AutomationElements;
using FlaUI.Core.Conditions;
using FlaUI.Core.Definitions;
using FlaUI.UIA2;
using FlaUI.UIA3;
using GRPCCommon.Protobuf.Common;
using GRPCCommon.Protobuf.NativeMessage;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using System.Drawing;
using UIAutomation.BrowserExtensions;
using UIAutomation.Elements;
using UIAutomation.Exceptions;

namespace UIAutomation
{
    /// <summary>
    /// 执行具体的UI操作
    /// </summary>
    public class UIAutomation
    {
        private readonly UIA2Automation uia2Automation;
        private readonly UIA3Automation uia3Automation;
        private readonly IServiceProvider serviceProvider;
        private readonly ILogger<UIAutomation> logger;

        private static string[] propertyNames = { "ClassName", "ControlType", "AutomationId", "Name" };

        public UIAutomation(
            ILogger<UIAutomation> logger,
            UIA2Automation uia2Automation,
            UIA3Automation uia3Automation,
            IServiceProvider serviceProvider)
        {
            this.logger = logger;
            this.uia2Automation = uia2Automation;
            this.uia3Automation = uia3Automation;
            this.serviceProvider = serviceProvider;
        }

        #region 新版

        internal ElementBase FromPoint(int x, int y, int parentDepth = 1, AutomationType automationType = AutomationType.UIA2)
        {
            // 返回单一元素，桌面或者html
            // 获取html元素的时候，创建一个元素的缓存，返回一个元素的临时id
            this.logger.LogInformation("UIAutomation From Point");
            AutomationBase automationBase = this.GetAutomation(automationType);

            Point point = new Point(x, y);
            AutomationElement automationElement = automationBase.FromPoint(point);

            // 判断是否是浏览器中
            BrowserExtension? browserExtension;
            AutomationElement? document;
            if (this.InBrowser(automationElement, out browserExtension, out document))
            {
                // 浏览器元素
                FromPointRequest request = new FromPointRequest
                {
                    Position = new Position
                    {
                        X= x,
                        Y=y
                    },
                    ParentDepth = parentDepth,
                };
                SetRelativePosition(request.Position, document);
                FromPointResponse response = browserExtension.FromPoint(request);
                if (response.Success)
                {
                    return new HTMLElement(response.Attribute, browserExtension);
                }
                else
                {
                    throw new BrowserExtensionException(response.Error.Message);
                }
            }
            else
            {
                // 桌面元素
                return new WindowElement(automationElement);
            }
        }

        internal ElementBase Find(GRPCCommon.Protobuf.Common.Attribute attribute,
            AutomationType automationType = AutomationType.UIA2)
        {
            throw new NotImplementedException();
        }

        internal AutomationBase GetAutomation(AutomationType automationType = AutomationType.UIA2)
        {
            switch (automationType)
            {
                case AutomationType.UIA2:
                    return this.uia2Automation;
                case AutomationType.UIA3:
                    return this.uia3Automation;
            }
            throw new Exception($"uia类型错误:{automationType}");
        }

        #endregion

        #region 私有方法
        
        /// <summary>
        /// 判断是否在浏览器中
        /// </summary>
        /// <param name="automationElement"></param>
        /// <param name="result"></param>
        /// <returns></returns>
        private bool InBrowser(AutomationElement automationElement,
            out BrowserExtension? result,
            out AutomationElement? document)
        {
            result=null;
            document=null;
            // 判断是否是浏览器中
            // 把自动注入的类添加到处理列表里面
            IEnumerable<BrowserExtension> extensions = this.serviceProvider.GetServices<BrowserExtension>();
            foreach (BrowserExtension extension in extensions)
            {
                // html部分的根容器
                //AutomationElement? document;
                if (extension.InBrowserDocument(automationElement, out document) && document != null)
                {
                    // 获取鼠标在html中的位置
                    result= extension;
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        /// 
        /// </summary>
        private static void SetRelativePosition(Position position, AutomationElement document)
        {
            int newX = position.X- document.BoundingRectangle.Left;
            int newY = position.Y- document.BoundingRectangle.Top;
            //Point p = AutomationElementRelativePosition(position.X, position.Y, document);
            position.X = newX;
            position.Y = newY;
        }

        /// <summary>
        /// 鼠标对应某个元素的相对位置
        /// </summary>
        private static Point AutomationElementRelativePosition(int x, int y, AutomationElement element)
        {
            int newX = x- element.BoundingRectangle.Left;
            int newY = y- element.BoundingRectangle.Top;
            return new Point(newX, newY);
        }

        /// <summary>
        /// 读取元素的属性
        /// </summary>
        /// <param name="element"></param>
        /// <returns></returns>
        private static GRPCCommon.Protobuf.Common.Attribute LoadAttributes(AutomationElement automationElement)
        {
            GRPCCommon.Protobuf.Common.Attribute attribute = new();
            attribute.Values.Add("ClassName", $"{automationElement.ClassName}");
            attribute.Values.Add("ControlType", $"{automationElement.ControlType}");
            attribute.Values.Add("AutomationId", $"{automationElement.AutomationId}");
            attribute.Values.Add("Name", $"{automationElement.Name}");
            attribute.ElementType = ElementType.Form;
            return attribute;
        }

        #endregion

        /// <summary>
        /// 获取元素的属性
        /// </summary>
        private static void LoadDetails(AutomationElement element)
        {
            // element.ControlType;
        }

    }
}
