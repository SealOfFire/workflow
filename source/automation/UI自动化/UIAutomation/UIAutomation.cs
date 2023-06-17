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

        internal ElementBase 通过鼠标位置获取元素(int x, int y, AutomationType automationType = AutomationType.UIA2)
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
                    }
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

        internal void 设置元素高亮()
        {
            // 传入元素 调用元素的高亮方法
            // 桌面元素，直接高亮
            // html元素，调用通过临时id高亮元素的插件接口
        }

        internal void 查找元素()
        {
            // 传入完整的元素父子结构
            // 桌面元素直接返回
            // 浏览器元素，找到元素后，创建一个浏览器的临时id。返回浏览器元素
            // 临时id是为了高亮。后续的click等操作使用的
        }

        internal void 拾取元素()
        {
            // 传入鼠标坐标。返回完整的元素识别列表
            // 拾取元素运行速度会比鼠标悬浮慢。
            // 通过传入的参数来判断返回单一元素，还是返回完整元素列表
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

        ///// <summary>
        ///// 鼠标悬浮高亮
        ///// </summary>
        ///// <param name="request"></param>
        //internal GRPCCommon.Protobuf.HoverResponse Hover(GRPCCommon.Protobuf.HoverRequest request)
        //{
        //    this.logger.LogInformation("Hover");
        //    AutomationBase automationBase = this.GetAutomation((AutomationType)request.AutomationType);

        //    Point point = new Point(request.Position.X, request.Position.Y);
        //    AutomationElement automationElement = automationBase.FromPoint(point);

        //    // 返回值
        //    GRPCCommon.Protobuf.HoverResponse? response = null;

        //    // 判断是否是浏览器中
        //    BrowserExtension? browserExtension;
        //    AutomationElement? document;
        //    if (this.InBrowser(automationElement, out browserExtension, out document))
        //    {
        //        // 浏览器元素
        //        SetRelativePosition(request.Position, document);
        //        response = browserExtension.Hover(request);
        //    }
        //    else
        //    {
        //        // 桌面元素
        //        // 返回的元素是桌面元素
        //        response = new GRPCCommon.Protobuf.HoverResponse
        //        {
        //            Id=request.Id,
        //            Command="hover",
        //            Success=true,
        //            Attribute = LoadAttributes(automationElement)  // 设置返回元素的属性值
        //        };

        //        // 设置桌面元素的高亮
        //        Color color = ColorTranslator.FromHtml(request.Highlight.Color);
        //        TimeSpan duration = TimeSpan.FromMilliseconds(request.Highlight.Duration);
        //        Task.Run(() =>
        //        {
        //            automationElement.DrawHighlight(false, color, duration);
        //        });
        //    }

        //    return response;
        //}

        ///// <summary>
        ///// 鼠标拾取
        ///// </summary>
        //internal GRPCCommon.Protobuf.PickUpResponse PickUp(GRPCCommon.Protobuf.PickUpRequest request)
        //{
        //    this.logger.LogInformation("PickUp");
        //    AutomationBase automationBase = this.GetAutomation((AutomationType)request.AutomationType);

        //    Point point = new Point(request.Position.X, request.Position.Y);
        //    AutomationElement automationElement = automationBase.FromPoint(point);

        //    // 返回值
        //    GRPCCommon.Protobuf.PickUpResponse? response = null;

        //    // 判断是否是浏览器中
        //    BrowserExtension? browserExtension;
        //    AutomationElement? document;
        //    if (this.InBrowser(automationElement, out browserExtension, out document))
        //    {
        //        // 浏览器元素
        //        SetRelativePosition(request.Position, document);
        //        response = browserExtension.PickUp(request);
        //    }
        //    else
        //    {
        //        // 桌面元素
        //        // 返回的元素是桌面元素
        //        response = new GRPCCommon.Protobuf.PickUpResponse
        //        {
        //            Id=request.Id,
        //            Command="hover",
        //            Success=true,
        //            Attribute = LoadAttributes(automationElement)  // 设置返回元素的属性值
        //        };

        //    }

        //    return response;
        //}

        ///// <summary>
        ///// 高亮元素
        ///// </summary>
        //internal GRPCCommon.Protobuf.HighlightResponse Highlight(GRPCCommon.Protobuf.HighlightRequest request)
        //{
        //    // TODO 查找元素。需要做一个共同功能。
        //    throw new NotImplementedException();
        //}

        #endregion

        #region 旧版

        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="automationType"></param>
        /// <returns></returns>
        internal ElementBase FromPoint(int x, int y, AutomationType automationType)
        {
            AutomationBase automationBase = this.GetAutomation(automationType);
            AutomationElement automationElement = automationBase.FromPoint(new System.Drawing.Point(x, y));

            ElementBase result = new WindowElement(automationElement);

            // 判断是否是浏览器中
            // 把自动注入的类添加到处理列表里面
            IEnumerable<BrowserExtension> extensions = this.serviceProvider.GetServices<BrowserExtension>();
            foreach (BrowserExtension extension in extensions)
            {
                // html部分的根容器
                AutomationElement? document;
                if (extension.InBrowserDocument(automationElement, out document) && document != null)
                {
                    // 获取鼠标在html中的位置
                    dynamic position = AutomationElementRelativePosition(x, y, document);
                    result = extension.FromPoint(position.x, position.y);
                    // 符合浏览器插件条件，执行完退出循环。不遍历其他浏览器条件了
                    break;
                }
            }

            //foreach (BrowserExtension extension in this.extensions)
            //{
            //    if (extension.InBrowser(automationElement))
            //    {
            //        result = extension.FromPoint(x, y);
            //    }
            //}

            //Task.Run(() =>
            //{
            //    automationElement.DrawHighlight(false, Color.Red, TimeSpan.FromSeconds(5));
            //});

            return result;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="conditions"></param>
        /// <param name="automationType"></param>
        /// <returns></returns>
        internal ElementBase? FindElement(Dictionary<string, object>[] conditions,
           AutomationType automationType = AutomationType.UIA2)
        {
            if (conditions == null || conditions.Length <=0)
            {
                return null;
            }
            else
            {
                AutomationBase automationBase = this.GetAutomation(automationType);
                AutomationElement rootElement = automationBase.GetDesktop();

                // condition[0] 是桌面 [1] 是应用程序窗口
                ConditionBase condition1 = WindowElement.ConvertConditionBase(conditions[1], automationBase.ConditionFactory);
                AutomationElement[] firstResult = rootElement.FindAll(TreeScope.Children, condition1);
                WindowElement[] windowElements = WindowElement.Create(firstResult); // 第一级的窗口一定是win窗口

                ElementBase[] elements = windowElements;
                for (int i = 2; i< conditions.Length-1; i++)
                {
                    elements = this.FindChildrenElement(elements, conditions[i]);
                    if (firstResult == null)
                    {
                        // 没找到元素
                        return null;
                    }
                }

                // 查询结果
                if (firstResult.Length >1)
                {
                    // 找到多个符合条件的元素
                    return null;
                }
                else if (firstResult.Length == 0)
                {
                    // 没找到元素
                    return null;
                }
                else
                {
                    return windowElements[0];
                }
            }
        }

        /// <summary>
        /// 根据条件查找子元素
        /// </summary>
        /// <param name="automationElements"></param>
        /// <param name="condition"></param>
        /// <returns></returns>
        private ElementBase[] FindChildrenElement(ElementBase[] automationElements, Dictionary<string, object> condition)
        {
            List<ElementBase> result = new List<ElementBase>();
            foreach (ElementBase element in automationElements)
            {
                ElementBase[] found = element.FindAllChildren(condition);

                if (found !=null)
                {
                    result.AddRange(found);
                }
            }
            return result.ToArray();
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
