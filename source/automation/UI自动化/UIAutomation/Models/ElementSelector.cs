using FlaUI.Core;
using FlaUI.Core.AutomationElements;
using FlaUI.Core.Conditions;
using FlaUI.Core.Definitions;
using FlaUI.Core.Exceptions;

namespace UIAutomation.Models
{
    /// <summary>
    /// 元素选择器
    /// </summary>
    public class ElementSelector
    {
        /// <summary>
        /// 可以作为检索条件的属性列表
        /// </summary>
        public static string[] PropertyIds = {
            "AutomationId",
            "Name",
            "ClassName",
            "ControlType",
            //"LocalizedControlType",
            //"FrameworkType",
            //"FrameworkId",
            //"ProcessId",
            //"IsEnabled",
            //"IsOffscreen",
            //"BoundingRectangle",
            //"HelpText",
            //"IsPassword",
            //"NativeWindowHandle"
        };

        /// <summary>
        /// 属性列表
        /// </summary>
        private Dictionary<string, object> properties;

        public ElementSelector? Parent { get; set; }
        public ElementSelector[]? Children { get; set; }
        public Dictionary<string, object> Properties { get { return properties; } }
        internal AutomationElement? AutomationElement { get; set; }

        public ElementSelector(AutomationElement automationElement)
        {
            this.properties = new Dictionary<string, object>();
            this.AutomationElement = automationElement;
        }

        public ElementSelector()
        {
            this.properties = new Dictionary<string, object>();
        }

        public void LoadDetails()
        {
            if (this.AutomationElement == null)
            {
                throw new Exception("缺少AutomationElement");
            }
            ElementSelector.LoadDetails(this.AutomationElement, this);
        }

        #region 静态方法

        public static void LoadDetails(AutomationElement automationElement, ElementSelector elementSelector)
        {
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
                var elementCached = automationElement.FindFirst(FlaUI.Core.Definitions.TreeScope.Element, TrueCondition.Default);
                if (elementCached != null)
                {
                    elementSelector.properties.Add("AutomationId", elementCached.Properties.AutomationId.ValueOrDefault);
                    elementSelector.properties.Add("Name", elementCached.Properties.Name.ValueOrDefault);
                    elementSelector.properties.Add("ClassName", elementCached.Properties.ClassName.ValueOrDefault);
                    elementSelector.properties.Add("ControlType", elementCached.Properties.ControlType.ValueOrDefault);
                    elementSelector.properties.Add("LocalizedControlType", elementCached.Properties.LocalizedControlType.ValueOrDefault);
                    elementSelector.properties.Add("FrameworkType", elementCached.FrameworkType);
                    elementSelector.properties.Add("FrameworkId", elementCached.Properties.FrameworkId.ValueOrDefault);
                    elementSelector.properties.Add("ProcessId", elementCached.Properties.ProcessId.ValueOrDefault);
                    elementSelector.properties.Add("IsEnabled", elementCached.Properties.IsEnabled.ValueOrDefault);
                    elementSelector.properties.Add("IsOffscreen", elementCached.Properties.IsOffscreen.ValueOrDefault); // TODO 不支持
                    elementSelector.properties.Add("BoundingRectangle", elementCached.Properties.BoundingRectangle.ValueOrDefault);
                    elementSelector.properties.Add("HelpText", elementCached.Properties.HelpText.ValueOrDefault);
                    elementSelector.properties.Add("IsPassword", elementCached.Properties.IsPassword.ValueOrDefault); // TODO 不支持

                    var boundingRectangle = elementCached.Properties.BoundingRectangle;
                    var nativeWindowHandle = elementCached.Properties.NativeWindowHandle.ValueOrDefault;
                    var nativeWindowHandleString = "Not Supported";
                    if (nativeWindowHandle != default(IntPtr))
                    {
                        nativeWindowHandleString = String.Format("{0} ({0:X8})", nativeWindowHandle.ToInt32());
                        elementSelector.properties.Add("NativeWindowHandle", nativeWindowHandleString);
                    }
                }
            }
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
                    return default(T);
                }
            }
        }

        #endregion
    }
}
