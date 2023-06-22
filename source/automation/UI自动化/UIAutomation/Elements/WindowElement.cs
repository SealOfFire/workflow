using FlaUI.Core;
using FlaUI.Core.AutomationElements;
using FlaUI.Core.Conditions;
using FlaUI.Core.Definitions;
using System.Drawing;
using System.Windows;
using UIAutomation.Models;

namespace UIAutomation.Elements
{
    /// <summary>
    /// 窗口元素
    /// </summary>
    internal class WindowElement : ElementBase
    {
        private AutomationElement automationElement;
        private string automationId = string.Empty;
        private string className = string.Empty;
        private string name = string.Empty;
        private ControlType controlType;
        private string nativeWindowHandle = string.Empty;
        private Rectangle boundingRectangle;

        #region 属性

        public string Name
        {
            get { return this.name; }
        }

        public ControlType ControlType
        {
            get { return this.controlType; }
        }

        public string AutomationId
        {
            get { return this.automationId; }
        }

        public string ClassName
        {
            get { return this.className; }
        }

        public Rectangle BoundingRectangle
        {
            get { return this.boundingRectangle; }
        }

        #endregion

        #region 构造函数

        public WindowElement(AutomationElement automationElement,
             int parentDepth = 1)
        {
            this.automationElement = automationElement;
            this.attribute = new GRPCCommon.Protobuf.Common.Attribute();

            automationElement.Properties.Name.TryGetValue(out this.name);
            automationElement.Properties.ClassName.TryGetValue(out this.className);
            automationElement.Properties.ControlType.TryGetValue(out this.controlType);
            automationElement.Properties.AutomationId.TryGetValue(out this.automationId);

            this.attribute = this.LoadParent(automationElement, this.attribute, parentDepth);

            //if (parentDepth>0)
            //{
            //    // 递归加载父级
            //    this.attribute = this.LoadParent(automationElement, this.attribute, parentDepth);
            //}
            //else
            //{
            //    this.attribute = LoadAttribute(automationElement);
            //}
        }

        #endregion

        #region 重写方法

        internal override void Highlight(GRPCCommon.Protobuf.Common.Highlight highlight)
        {
            Color color = ColorTranslator.FromHtml(highlight.Color);
            TimeSpan duration = TimeSpan.FromMilliseconds(highlight.Duration);
            Task.Run(() =>
            {
                this.automationElement.DrawHighlight(false, color, duration);
            });
        }

        internal override ElementSelector ToElementSelector()
        {
            ElementSelector1 elementSelector = new ElementSelector1();
            throw new NotImplementedException();
        }

        internal override void Click()
        {
            throw new NotImplementedException();
        }

        #endregion

        /// <summary>
        /// 
        /// </summary>
        /// <param name="automationElement"></param>
        /// <returns></returns>
        internal GRPCCommon.Protobuf.Common.Attribute LoadParent(AutomationElement automationElement,
             GRPCCommon.Protobuf.Common.Attribute attributeParent,
            int parentDepth = 1)
        {
            GRPCCommon.Protobuf.Common.Attribute attribute = LoadAttribute(automationElement);

            int index = 1;
            while (automationElement.Parent !=null && (index< parentDepth || parentDepth<0))
            {
                automationElement = automationElement.Parent;
                GRPCCommon.Protobuf.Common.Attribute parentAttr = LoadAttribute(automationElement);
                parentAttr.Children.Add(attribute);
                attribute = parentAttr;
                index++;
            }

            return attribute;
        }

        internal GRPCCommon.Protobuf.Common.Attribute LoadAttribute(AutomationElement automationElement)
        {
            GRPCCommon.Protobuf.Common.Attribute attribute = new GRPCCommon.Protobuf.Common.Attribute();
            attribute.ElementType = GRPCCommon.Protobuf.Common.ElementType.Form;

            string name = string.Empty;
            if (automationElement.Properties.Name.TryGetValue(out name))
            {
                attribute.Name = name;
            }

            string className = string.Empty;
            if (automationElement.Properties.ClassName.TryGetValue(out className))
            {
                attribute.ClassName = className;
            }

            ControlType controlType = ControlType.Unknown;
            if (automationElement.Properties.ControlType.TryGetValue(out controlType))
            {
                attribute.ControlType = (int)controlType;
            }

            string automationId = string.Empty;
            if (automationElement.Properties.AutomationId.TryGetValue(out automationId))
            {
                attribute.AutomationId = automationId;
            }
            return attribute;
        }

        internal void LoadDetails()
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
                    this.automationId = elementCached.Properties.AutomationId.ValueOrDefault;
                    this.className = elementCached.Properties.ClassName.ValueOrDefault;
                    this.name = elementCached.Properties.Name.ValueOrDefault;
                    this.controlType = elementCached.Properties.ControlType.ValueOrDefault;

                    //elementSelector.properties.Add("AutomationId", elementCached.Properties.AutomationId.ValueOrDefault);
                    //elementSelector.properties.Add("Name", elementCached.Properties.Name.ValueOrDefault);
                    //elementSelector.properties.Add("ClassName", elementCached.Properties.ClassName.ValueOrDefault);
                    //elementSelector.properties.Add("ControlType", elementCached.Properties.ControlType.ValueOrDefault);
                    //elementSelector.properties.Add("LocalizedControlType", elementCached.Properties.LocalizedControlType.ValueOrDefault);
                    //elementSelector.properties.Add("FrameworkType", elementCached.FrameworkType);
                    //elementSelector.properties.Add("FrameworkId", elementCached.Properties.FrameworkId.ValueOrDefault);
                    //elementSelector.properties.Add("ProcessId", elementCached.Properties.ProcessId.ValueOrDefault);
                    //elementSelector.properties.Add("IsEnabled", elementCached.Properties.IsEnabled.ValueOrDefault);
                    //elementSelector.properties.Add("IsOffscreen", elementCached.Properties.IsOffscreen.ValueOrDefault); // TODO 不支持
                    //elementSelector.properties.Add("BoundingRectangle", elementCached.Properties.BoundingRectangle.ValueOrDefault);
                    //elementSelector.properties.Add("HelpText", elementCached.Properties.HelpText.ValueOrDefault);
                    //elementSelector.properties.Add("IsPassword", elementCached.Properties.IsPassword.ValueOrDefault); // TODO 不支持

                    var boundingRectangle = elementCached.Properties.BoundingRectangle;
                    var nativeWindowHandle = elementCached.Properties.NativeWindowHandle.ValueOrDefault;
                    var nativeWindowHandleString = "Not Supported";
                    if (nativeWindowHandle != default(IntPtr))
                    {
                        nativeWindowHandleString = String.Format("{0} ({0:X8})", nativeWindowHandle.ToInt32());
                        this.nativeWindowHandle = nativeWindowHandleString;
                    }
                }
            }
        }

        #region 静态方法

        internal static ConditionBase ConvertConditionBase(Dictionary<string, object> condition, ConditionFactory cf)
        {
            List<PropertyCondition> properties = new List<PropertyCondition>();
            //ConditionFactory cf = this.automationElement.Automation.ConditionFactory;
            // 转换查询条件啊
            string name = "AutomationId";
            if (condition.Keys.Contains(name) && !string.IsNullOrEmpty((string)condition[name]))
                properties.Add(cf.ByAutomationId((string)condition[name]));

            name = "Name";
            if (condition.Keys.Contains(name) && !string.IsNullOrEmpty((string)condition[name]))
                properties.Add(cf.ByName((string)condition[name]));

            name = "ClassName";
            if (condition.Keys.Contains(name) && !string.IsNullOrEmpty((string)condition[name]))
                properties.Add(cf.ByClassName((string)condition[name]));

            name = "ControlType";
            if (condition.Keys.Contains(name))
                properties.Add(cf.ByControlType((ControlType)condition[name]));

            ConditionBase conditionBase = properties[0];
            for (int i = 1; i < properties.Count; i++)
            {
                conditionBase = conditionBase.And(properties[i]);
            }
            return conditionBase;
        }

        internal static WindowElement[] Create(AutomationElement[] automationElements)
        {
            WindowElement[] result = new WindowElement[automationElements.Length];
            int index = 0;
            foreach (AutomationElement automationElement in automationElements)
            {
                result[index++] = new WindowElement(automationElement);
            }
            return result;
        }

        #endregion
    }
}
