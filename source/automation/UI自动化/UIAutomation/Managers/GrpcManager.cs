using FlaUI.Core;
using FlaUI.Core.AutomationElements;
using FlaUI.Core.Conditions;
using FlaUI.Core.Definitions;
using FlaUI.Core.Exceptions;
using Microsoft.Extensions.Logging;
using UIAutomationServer;

namespace UIAutomation.Managers
{
    /// <summary>
    /// grpc接口和元素识别接口之间的转换
    /// TODO 通过grpc调用很慢
    /// </summary>
    public class GrpcManager
    {
        private readonly ILogger<GrpcManager> logger;
        private readonly Selector selector;

        public GrpcManager(ILogger<GrpcManager> logger, Selector selector)
        {
            this.selector = selector;
            this.logger = logger;
        }

        /// <summary>
        /// 鼠标悬停在元素上
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="color"></param>
        /// <param name="duration"></param>
        /// <param name="uiaType"></param>
        /// <returns></returns>
        public void HoverElement(int x, int y,
            System.Drawing.Color color,
            TimeSpan duration,
            UIAType uiaType = UIAType.Uia2)
        {
            logger.LogTrace("HoverElement");

            AutomationElement? automationElement = selector.FromPoint(x, y, Convert(uiaType));
            if (automationElement == null)
            {
                // 没找到元素
                // return null;
            }
            else
            {
                // 高亮
                Task.Run(() => { automationElement.DrawHighlight(false, color, duration); });
            }
        }

        /// <summary>
        /// 鼠标选择元素
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="uiaType"></param>
        /// <returns></returns>
        public Element? PickUpElement(int x, int y,
            UIAType uiaType = UIAType.Uia2)
        {
            logger.LogTrace("PickUpElement");
            AutomationElement? automationElement = selector.PickUpElement(x, y, Convert(uiaType));

            if (automationElement == null)
            {
                // 没找到元素
                return null;
            }
            else
            {
                Element element = Convert(automationElement);
                return element;
            }
        }

        /// <summary>
        /// 高亮
        /// </summary>
        /// <param name="selector">要高亮的元素</param>
        /// <param name="color"></param>
        /// <param name="duration"></param>
        /// <param name="uiaType"></param>
        /// <returns></returns>
        public AutomationElement? Highlight(Element selector,
            System.Drawing.Color color,
            TimeSpan duration,
            UIAType uiaType = UIAType.Uia2)
        {
            // 元素转换为查询条件
            //ConditionFactory cf;

            List<ConditionBase> conditions = new List<ConditionBase>();
            AutomationBase automationBase = this.selector.GetAutomation(Convert(uiaType));
            Conditions(selector, conditions, automationBase.ConditionFactory);

            AutomationElement? automationElement = this.selector.FindElement(conditions, Convert(uiaType));
            if (automationElement == null)
            {
                // 没有找到要高亮的元素
                return null;
            }
            else
            {
                // 高亮
                Task.Run(() => { automationElement.DrawHighlight(false, color, duration); });
                return automationElement;
            }
        }

        private static Element LoadDetails(AutomationElement automationElement)
        {
            Element element = new Element();
            ElementProperties properties = new ElementProperties();

            CacheRequest cacheRequest = new CacheRequest();
            cacheRequest.TreeScope = TreeScope.Element;
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.AutomationId);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.ClassName);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.ControlType);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.FrameworkId);
            //没有FrameworkType
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.LocalizedControlType);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.HelpText);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.Name);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.ProcessId);
            // text
            // value
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.BoundingRectangle);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.NativeWindowHandle);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.IsEnabled);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.IsOffscreen);
            cacheRequest.Add(automationElement.Automation.PropertyLibrary.Element.IsPassword);
            using (cacheRequest.Activate())
            {
                var elementCached = automationElement.FindFirst(TreeScope.Element, TrueCondition.Default);
                if (elementCached != null)
                {
                    properties.StringProperties.Add("AutomationId", SetValue(elementCached.Properties.AutomationId));
                    properties.StringProperties.Add("Name", SetValue(elementCached.Properties.Name));
                    properties.StringProperties.Add("ClassName", SetValue(elementCached.Properties.ClassName));
                    properties.StringProperties.Add("ControlType", elementCached.Properties.ControlType.ToString());
                    properties.StringProperties.Add("LocalizedControlType", elementCached.Properties.LocalizedControlType);
                    properties.StringProperties.Add("FrameworkType", elementCached.FrameworkType.ToString());
                    properties.StringProperties.Add("FrameworkId", elementCached.Properties.FrameworkId);
                    properties.IntgerProperties.Add("ProcessId", elementCached.Properties.ProcessId);
                    properties.BoolProperties.Add("IsEnabled", elementCached.Properties.IsEnabled);
                    properties.BoolProperties.Add("IsOffscreen", SetValue(elementCached.Properties.IsOffscreen)); // TODO 不支持
                    properties.StringProperties.Add("BoundingRectangle", elementCached.Properties.BoundingRectangle.ToString());
                    properties.StringProperties.Add("HelpText", SetValue(elementCached.Properties.HelpText));
                    properties.BoolProperties.Add("IsPassword", SetValue(elementCached.Properties.IsPassword)); // TODO 不支持

                    //element.AutomationId = elementCached.Properties.AutomationId;
                    element.AutomationId = SetValue(elementCached.Properties.AutomationId);
                    element.ClassName = elementCached.Properties.ClassName;
                    element.ControlType = Convert(elementCached.Properties.ControlType);
                    element.FrameworkId = elementCached.Properties.FrameworkId;
                    element.FrameworkType = Convert(elementCached.FrameworkType);
                    element.LocalizedControlType = elementCached.Properties.LocalizedControlType;
                    element.HelpText = SetValue(elementCached.Properties.HelpText);
                    element.Name = elementCached.Properties.Name;
                    element.ProcessId = elementCached.Properties.ProcessId;

                    var boundingRectangle = elementCached.Properties.BoundingRectangle;
                    var nativeWindowHandle = elementCached.Properties.NativeWindowHandle.ValueOrDefault;
                    var nativeWindowHandleString = "Not Supported";
                    if (nativeWindowHandle != default)
                    {
                        nativeWindowHandleString = string.Format("{0} ({0:X8})", nativeWindowHandle.ToInt32());
                        properties.StringProperties.Add("NativeWindowHandle", nativeWindowHandleString);
                    }

                    /*
                    var allSupportedPatterns = automationElement.GetSupportedPatterns();
                    PatternId[] allPatterns = automationElement.Automation.PatternLibrary.AllForCurrentFramework;
                    foreach (var pattern in allPatterns)
                    {
                        var hasPattern = allSupportedPatterns.Contains(pattern);
                        properties.Patterns.Add(pattern.Name + "Pattern", hasPattern ? "Yes" : "No");
                    }
                    */
                }
            }

            return element;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="automationProperty"></param>
        /// <returns></returns>
        private static T SetValue<T>(AutomationProperty<T> automationProperty)
        {
            try
            {
                return automationProperty.Value;
            }
            catch (PropertyNotSupportedException)
            {
                // 不支持属性，返回空字符串
                if (typeof(T) == typeof(string))
                {
                    return (T)("" as object);
                }
                else
                {
                    return default;
                }
            }
        }

        /// <summary>
        /// 元素识别结果转成检索条件
        /// </summary>
        /// <param name="element"></param>
        /// <param name="conditions"></param>
        /// <param name="cf"></param>
        private static void Conditions(Element element, List<ConditionBase> conditions, ConditionFactory cf)
        {
            List<PropertyCondition> properties = new List<PropertyCondition>();

            if (!string.IsNullOrEmpty(element.AutomationId))
                properties.Add(cf.ByAutomationId(element.AutomationId));

            if (!string.IsNullOrEmpty(element.ClassName))
                properties.Add(cf.ByClassName(element.ClassName));

            properties.Add(cf.ByControlType(Convert(element.ControlType)));

            if (!string.IsNullOrEmpty(element.FrameworkId))
                properties.Add(cf.ByFrameworkId(element.FrameworkId));

            if (element.FrameworkType != UIAutomationServer.FrameworkType.None)
                properties.Add(cf.ByFrameworkType(Convert(element.FrameworkType)));

            if (!string.IsNullOrEmpty(element.HelpText))
                properties.Add(cf.ByHelpText(element.HelpText));

            if (!string.IsNullOrEmpty(element.LocalizedControlType))
                properties.Add(cf.ByLocalizedControlType(element.LocalizedControlType));

            if (!string.IsNullOrEmpty(element.Name))
                properties.Add(cf.ByName(element.Name));

            if (element.ProcessId != 0)
                properties.Add(cf.ByProcessId(element.ProcessId));

            if (!string.IsNullOrEmpty(element.Text))
                properties.Add(cf.ByText(element.Text));

            if (!string.IsNullOrEmpty(element.Value))
                properties.Add(cf.ByValue(element.Value));

            ConditionBase conditionBase = properties[0];
            for (int i = 1; i < properties.Count; i++)
            {
                conditionBase = conditionBase.And(properties[i]);
            }
            conditions.Insert(0, conditionBase);
            if (element.Parent != null)
            {
                Conditions(element.Parent, conditions, cf);
            }
        }

        #region grpc数据和flaui数据之间转换

        /// <summary>
        /// 
        /// </summary>
        /// <param name="automationElement"></param>
        /// <param name="parent">递归处理父级别元素</param>
        /// <returns></returns>
        private static Element Convert(AutomationElement automationElement)
        {
            Element element = LoadDetails(automationElement);

            if (automationElement.Parent != null)
            {
                if (automationElement.Parent.ClassName == "#32769"
                    && automationElement.Parent.ControlType == FlaUI.Core.Definitions.ControlType.Pane)
                {
                    // 窗口
                    //selectorReponse.Window = element;
                }
                else
                {
                    // 元素
                    //element.Parent = Convert(automationElement.Parent);
                    //selectorReponse.Element = element;
                }
                element.Parent = Convert(automationElement.Parent);
            }
            return element;
        }

        private static FlaUI.Core.Definitions.ControlType Convert(UIAutomationServer.ControlType controlType)
        {
            switch (controlType)
            {
                case UIAutomationServer.ControlType.Unknown:
                    return FlaUI.Core.Definitions.ControlType.Unknown;
                case UIAutomationServer.ControlType.AppBar:
                    return FlaUI.Core.Definitions.ControlType.AppBar;
                case UIAutomationServer.ControlType.Button:
                    return FlaUI.Core.Definitions.ControlType.Button;
                case UIAutomationServer.ControlType.Calendar:
                    return FlaUI.Core.Definitions.ControlType.Calendar;
                case UIAutomationServer.ControlType.CheckBox:
                    return FlaUI.Core.Definitions.ControlType.CheckBox;
                case UIAutomationServer.ControlType.ComboBox:
                    return FlaUI.Core.Definitions.ControlType.ComboBox;
                case UIAutomationServer.ControlType.Custom:
                    return FlaUI.Core.Definitions.ControlType.Custom;
                case UIAutomationServer.ControlType.DataGrid:
                    return FlaUI.Core.Definitions.ControlType.DataGrid;
                case UIAutomationServer.ControlType.DataItem:
                    return FlaUI.Core.Definitions.ControlType.DataItem;
                case UIAutomationServer.ControlType.Document:
                    return FlaUI.Core.Definitions.ControlType.Document;
                case UIAutomationServer.ControlType.Edit:
                    return FlaUI.Core.Definitions.ControlType.Edit;
                case UIAutomationServer.ControlType.Group:
                    return FlaUI.Core.Definitions.ControlType.Group;
                case UIAutomationServer.ControlType.Header:
                    return FlaUI.Core.Definitions.ControlType.Header;
                case UIAutomationServer.ControlType.HeaderItem:
                    return FlaUI.Core.Definitions.ControlType.HeaderItem;
                case UIAutomationServer.ControlType.Hyperlink:
                    return FlaUI.Core.Definitions.ControlType.Hyperlink;
                case UIAutomationServer.ControlType.Image:
                    return FlaUI.Core.Definitions.ControlType.Image;
                case UIAutomationServer.ControlType.List:
                    return FlaUI.Core.Definitions.ControlType.List;
                case UIAutomationServer.ControlType.ListItem:
                    return FlaUI.Core.Definitions.ControlType.ListItem;
                case UIAutomationServer.ControlType.MenuBar:
                    return FlaUI.Core.Definitions.ControlType.MenuBar;
                case UIAutomationServer.ControlType.Menu:
                    return FlaUI.Core.Definitions.ControlType.Menu;
                case UIAutomationServer.ControlType.MenuItem:
                    return FlaUI.Core.Definitions.ControlType.MenuItem;
                case UIAutomationServer.ControlType.Pane:
                    return FlaUI.Core.Definitions.ControlType.Pane;
                case UIAutomationServer.ControlType.ProgressBar:
                    return FlaUI.Core.Definitions.ControlType.ProgressBar;
                case UIAutomationServer.ControlType.RadioButton:
                    return FlaUI.Core.Definitions.ControlType.RadioButton;
                case UIAutomationServer.ControlType.ScrollBar:
                    return FlaUI.Core.Definitions.ControlType.ScrollBar;
                case UIAutomationServer.ControlType.SemanticZoom:
                    return FlaUI.Core.Definitions.ControlType.SemanticZoom;
                case UIAutomationServer.ControlType.Separator:
                    return FlaUI.Core.Definitions.ControlType.Separator;
                case UIAutomationServer.ControlType.Slider:
                    return FlaUI.Core.Definitions.ControlType.Slider;
                case UIAutomationServer.ControlType.Spinner:
                    return FlaUI.Core.Definitions.ControlType.Spinner;
                case UIAutomationServer.ControlType.SplitButton:
                    return FlaUI.Core.Definitions.ControlType.SplitButton;
                case UIAutomationServer.ControlType.StatusBar:
                    return FlaUI.Core.Definitions.ControlType.StatusBar;
                case UIAutomationServer.ControlType.Tab:
                    return FlaUI.Core.Definitions.ControlType.Tab;
                case UIAutomationServer.ControlType.TabItem:
                    return FlaUI.Core.Definitions.ControlType.TabItem;
                case UIAutomationServer.ControlType.Table:
                    return FlaUI.Core.Definitions.ControlType.Table;
                case UIAutomationServer.ControlType.Text:
                    return FlaUI.Core.Definitions.ControlType.Text;
                case UIAutomationServer.ControlType.Thumb:
                    return FlaUI.Core.Definitions.ControlType.Thumb;
                case UIAutomationServer.ControlType.TitleBar:
                    return FlaUI.Core.Definitions.ControlType.TitleBar;
                case UIAutomationServer.ControlType.ToolBar:
                    return FlaUI.Core.Definitions.ControlType.ToolBar;
                case UIAutomationServer.ControlType.ToolTip:
                    return FlaUI.Core.Definitions.ControlType.ToolTip;
                case UIAutomationServer.ControlType.Tree:
                    return FlaUI.Core.Definitions.ControlType.Tree;
                case UIAutomationServer.ControlType.TreeItem:
                    return FlaUI.Core.Definitions.ControlType.TreeItem;
                case UIAutomationServer.ControlType.Window:
                    return FlaUI.Core.Definitions.ControlType.Window;
            }
            throw new Exception($"错误的枚举类型{controlType}");
        }

        private static UIAutomationServer.ControlType Convert(FlaUI.Core.Definitions.ControlType controlType)
        {
            switch (controlType)
            {
                case FlaUI.Core.Definitions.ControlType.Unknown:
                    return UIAutomationServer.ControlType.Unknown;
                case FlaUI.Core.Definitions.ControlType.AppBar:
                    return UIAutomationServer.ControlType.AppBar;
                case FlaUI.Core.Definitions.ControlType.Button:
                    return UIAutomationServer.ControlType.Button;
                case FlaUI.Core.Definitions.ControlType.Calendar:
                    return UIAutomationServer.ControlType.Calendar;
                case FlaUI.Core.Definitions.ControlType.CheckBox:
                    return UIAutomationServer.ControlType.CheckBox;
                case FlaUI.Core.Definitions.ControlType.ComboBox:
                    return UIAutomationServer.ControlType.ComboBox;
                case FlaUI.Core.Definitions.ControlType.Custom:
                    return UIAutomationServer.ControlType.Custom;
                case FlaUI.Core.Definitions.ControlType.DataGrid:
                    return UIAutomationServer.ControlType.DataGrid;
                case FlaUI.Core.Definitions.ControlType.DataItem:
                    return UIAutomationServer.ControlType.DataItem;
                case FlaUI.Core.Definitions.ControlType.Document:
                    return UIAutomationServer.ControlType.Document;
                case FlaUI.Core.Definitions.ControlType.Edit:
                    return UIAutomationServer.ControlType.Edit;
                case FlaUI.Core.Definitions.ControlType.Group:
                    return UIAutomationServer.ControlType.Group;
                case FlaUI.Core.Definitions.ControlType.Header:
                    return UIAutomationServer.ControlType.Header;
                case FlaUI.Core.Definitions.ControlType.HeaderItem:
                    return UIAutomationServer.ControlType.HeaderItem;
                case FlaUI.Core.Definitions.ControlType.Hyperlink:
                    return UIAutomationServer.ControlType.Hyperlink;
                case FlaUI.Core.Definitions.ControlType.Image:
                    return UIAutomationServer.ControlType.Image;
                case FlaUI.Core.Definitions.ControlType.List:
                    return UIAutomationServer.ControlType.List;
                case FlaUI.Core.Definitions.ControlType.ListItem:
                    return UIAutomationServer.ControlType.ListItem;
                case FlaUI.Core.Definitions.ControlType.MenuBar:
                    return UIAutomationServer.ControlType.MenuBar;
                case FlaUI.Core.Definitions.ControlType.Menu:
                    return UIAutomationServer.ControlType.Menu;
                case FlaUI.Core.Definitions.ControlType.MenuItem:
                    return UIAutomationServer.ControlType.MenuItem;
                case FlaUI.Core.Definitions.ControlType.Pane:
                    return UIAutomationServer.ControlType.Pane;
                case FlaUI.Core.Definitions.ControlType.ProgressBar:
                    return UIAutomationServer.ControlType.ProgressBar;
                case FlaUI.Core.Definitions.ControlType.RadioButton:
                    return UIAutomationServer.ControlType.RadioButton;
                case FlaUI.Core.Definitions.ControlType.ScrollBar:
                    return UIAutomationServer.ControlType.ScrollBar;
                case FlaUI.Core.Definitions.ControlType.SemanticZoom:
                    return UIAutomationServer.ControlType.SemanticZoom;
                case FlaUI.Core.Definitions.ControlType.Separator:
                    return UIAutomationServer.ControlType.Separator;
                case FlaUI.Core.Definitions.ControlType.Slider:
                    return UIAutomationServer.ControlType.Slider;
                case FlaUI.Core.Definitions.ControlType.Spinner:
                    return UIAutomationServer.ControlType.Spinner;
                case FlaUI.Core.Definitions.ControlType.SplitButton:
                    return UIAutomationServer.ControlType.SplitButton;
                case FlaUI.Core.Definitions.ControlType.StatusBar:
                    return UIAutomationServer.ControlType.StatusBar;
                case FlaUI.Core.Definitions.ControlType.Tab:
                    return UIAutomationServer.ControlType.Tab;
                case FlaUI.Core.Definitions.ControlType.TabItem:
                    return UIAutomationServer.ControlType.TabItem;
                case FlaUI.Core.Definitions.ControlType.Table:
                    return UIAutomationServer.ControlType.Table;
                case FlaUI.Core.Definitions.ControlType.Text:
                    return UIAutomationServer.ControlType.Text;
                case FlaUI.Core.Definitions.ControlType.Thumb:
                    return UIAutomationServer.ControlType.Thumb;
                case FlaUI.Core.Definitions.ControlType.TitleBar:
                    return UIAutomationServer.ControlType.TitleBar;
                case FlaUI.Core.Definitions.ControlType.ToolBar:
                    return UIAutomationServer.ControlType.ToolBar;
                case FlaUI.Core.Definitions.ControlType.ToolTip:
                    return UIAutomationServer.ControlType.ToolTip;
                case FlaUI.Core.Definitions.ControlType.Tree:
                    return UIAutomationServer.ControlType.Tree;
                case FlaUI.Core.Definitions.ControlType.TreeItem:
                    return UIAutomationServer.ControlType.TreeItem;
                case FlaUI.Core.Definitions.ControlType.Window:
                    return UIAutomationServer.ControlType.Window;
            }
            throw new Exception($"错误的枚举类型{controlType}");
        }

        private static UIAutomationServer.FrameworkType Convert(FlaUI.Core.FrameworkType frameworkType)
        {
            switch (frameworkType)
            {
                case FlaUI.Core.FrameworkType.None:
                    return UIAutomationServer.FrameworkType.None;
                case FlaUI.Core.FrameworkType.WinForms:
                    return UIAutomationServer.FrameworkType.WinForms;
                case FlaUI.Core.FrameworkType.Wpf:
                    return UIAutomationServer.FrameworkType.Wpf;
                case FlaUI.Core.FrameworkType.Xaml:
                    return UIAutomationServer.FrameworkType.Xaml;
                case FlaUI.Core.FrameworkType.Qt:
                    return UIAutomationServer.FrameworkType.Qt;
                case FlaUI.Core.FrameworkType.Unknown:
                    return UIAutomationServer.FrameworkType.Unknown2;
                case FlaUI.Core.FrameworkType.Win32:
                    return UIAutomationServer.FrameworkType.Win32;
            }
            throw new Exception($"错误的枚举类型{frameworkType}");
        }

        private static FlaUI.Core.FrameworkType Convert(UIAutomationServer.FrameworkType frameworkType)
        {
            switch (frameworkType)
            {
                case UIAutomationServer.FrameworkType.None:
                    return FlaUI.Core.FrameworkType.None;
                case UIAutomationServer.FrameworkType.WinForms:
                    return FlaUI.Core.FrameworkType.WinForms;
                case UIAutomationServer.FrameworkType.Wpf:
                    return FlaUI.Core.FrameworkType.Wpf;
                case UIAutomationServer.FrameworkType.Xaml:
                    return FlaUI.Core.FrameworkType.Xaml;
                case UIAutomationServer.FrameworkType.Qt:
                    return FlaUI.Core.FrameworkType.Qt;
                case UIAutomationServer.FrameworkType.Unknown2:
                    return FlaUI.Core.FrameworkType.Unknown;
                case UIAutomationServer.FrameworkType.Win32:
                    return FlaUI.Core.FrameworkType.Win32;
            }
            throw new Exception($"错误的枚举类型{frameworkType}");
        }

        private AutomationType Convert(UIAType uiaType)
        {
            switch (uiaType)
            {
                case UIAType.Uia2:
                    return AutomationType.UIA2;
                case UIAType.Uia3:
                    return AutomationType.UIA3;
            }
            throw new Exception($"错误的枚举类型{uiaType}");
        }

        #endregion
    }
}
