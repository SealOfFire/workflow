using FlaUI.Core;
using FlaUI.Core.AutomationElements;
using FlaUI.Core.Conditions;
using FlaUI.Core.Definitions;
using FlaUI.UIA2;
using FlaUI.UIA3;
using GRPCCommon.Protobuf.Common;
using GRPCCommon.Protobuf.NativeMessage;
using Microsoft.Extensions.Logging;
using System.Drawing;
using UIAutomation.BrowserExtensions;
using UIAutomation.Elements;
using UIAutomation.Ex;
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
        private readonly ILogger<UIAutomation> logger;
        private readonly ExtensionManager extensionManager;

        //private static string[] propertyNames = { "ClassName", "ControlType", "AutomationId", "Name" };

        public UIAutomation(
            ILogger<UIAutomation> logger,
            UIA2Automation uia2Automation,
            UIA3Automation uia3Automation,
            ExtensionManager extensionManager)
        {
            this.logger = logger;
            this.uia2Automation = uia2Automation;
            this.uia3Automation = uia3Automation;
            this.extensionManager=extensionManager;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="automationType"></param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
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


        #region 查找元素

        /// <summary>
        /// 查找鼠标位置的控件
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="parentDepth"></param>
        /// <param name="automationType"></param>
        /// <returns></returns>
        /// <exception cref="BrowserExtensionException"></exception>
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
                return new WindowElement(automationElement, parentDepth);
            }
        }

        /// <summary>
        /// 通过控件的属性查找控件
        /// </summary>
        /// <param name="browserType"></param>
        /// <param name="attribute"></param>
        /// <param name="automationType"></param>
        /// <returns></returns>
        /// <exception cref="ElementNotFoundException"></exception>
        /// <exception cref="BrowserExtensionException"></exception>
        internal ElementBase Find(BrowserType browserType,
            GRPCCommon.Protobuf.Common.Attribute attribute,
            AutomationType automationType = AutomationType.UIA2)
        {
            this.logger.LogInformation("UIAutomation Find");

            switch (attribute.ElementType)
            {
                case ElementType.Form:
                    // 查找桌面元素
                    // TODO
                    AutomationBase automationBase = this.GetAutomation(automationType);
                    AutomationElement? automationElement = Find(automationBase, attribute);
                    if (automationElement == null)
                    {
                        throw new ElementNotFoundException();
                    }
                    else
                    {
                        return new WindowElement(automationElement);
                    }
                case ElementType.Html:
                    // 查找浏览器元素
                    BrowserExtension extension = this.extensionManager.GetBrowserExtension(browserType);
                    FindRequest request = new FindRequest
                    {
                        Attribute=attribute,
                    };
                    FindResponse response = extension.Find(request);
                    if (response.Success)
                    {
                        return new HTMLElement(response.Attribute, extension);
                    }
                    else
                    {
                        throw new BrowserExtensionException(response.Error.Message);
                    }
                default:
                    throw new ElementNotFoundException("不支持的元素类型");
            }

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
            //IEnumerable<BrowserExtension> extensions = this.serviceProvider.GetServices<BrowserExtension>();
            IEnumerable<BrowserExtension> extensions = this.extensionManager.GetExtensions();
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

        /// <summary>
        /// 
        /// </summary>
        /// <param name="automationBase"></param>
        /// <param name="attribute"></param>
        private static AutomationElement? Find(AutomationBase automationBase, GRPCCommon.Protobuf.Common.Attribute attribute)
        {
            List<ConditionBase> conditions = new List<ConditionBase>();
            CreateCondition(automationBase.ConditionFactory, attribute, conditions);

            AutomationElement? element = automationBase.GetDesktop();

            // 查找元素
            int index = 1;
            while (true)
            {
                element = Find(element, conditions[index]);
                index++;
                if (index >= conditions.Count  || element==null)
                {
                    break;
                }
            }

            return element;
        }

        private static AutomationElement? Find(AutomationElement element, ConditionBase condition)
        {
            AutomationElement[] result = element.FindAllChildren(condition);
            if (result.Length>0)
            {
                return result[0];
            }
            return null;
        }

        private static void CreateCondition(ConditionFactory cf, GRPCCommon.Protobuf.Common.Attribute attribute, List<ConditionBase> conditions)
        {
            //List<PropertyCondition> properties = new List<PropertyCondition>();

            //PropertyCondition propertyCondition = null;
            ConditionBase? condition = null;

            if (attribute.HasAutomationId && !string.IsNullOrEmpty(attribute.AutomationId))
            {
                condition = cf.ByAutomationId(attribute.AutomationId);
            }

            if (attribute.HasName && !string.IsNullOrEmpty(attribute.Name))
            {
                if (condition == null)
                    condition = cf.ByName(attribute.Name);
                else
                    condition = condition.And(cf.ByName(attribute.Name));
            }

            if (attribute.HasControlType)
            {
                if (condition == null)
                    condition = cf.ByControlType((ControlType)attribute.ControlType);
                else
                    condition = condition.And(cf.ByControlType((ControlType)attribute.ControlType));
            }

            if (attribute.HasClassName && !string.IsNullOrEmpty(attribute.ClassName))
            {
                if (condition == null)
                    condition = cf.ByClassName(attribute.ClassName);
                else
                    condition = condition.And(cf.ByClassName(attribute.ClassName));
            }

            if (condition==null)
            {
                // TODO 没有条件是错的
            }
            else
            {
                conditions.Add(condition);
            }

            if (attribute.Children.Count>0)
            {
                CreateCondition(cf, attribute.Children[0], conditions);
            }

        }

        #endregion

    }
}
