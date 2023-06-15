using FlaUI.Core;
using FlaUI.Core.AutomationElements;
using FlaUI.Core.Conditions;
using Microsoft.Extensions.Logging;

namespace UIAutomation.Managers
{
    /// <summary>
    ///  web api接口和元素识别接口之间的转换
    ///  FlaUI和外部中间件
    /// </summary>
    public class ApiManager
    {
        private readonly ILogger<ApiManager> logger;
        private readonly Selector selector;

        public ApiManager(ILogger<ApiManager> logger, Selector selector)
        {
            this.selector = selector;
            this.logger = logger;
        }

        public Models.ElementSelector? HoverElement(int x, int y,
            System.Drawing.Color color,
            TimeSpan duration,
            AutomationType automationType = AutomationType.UIA2)
        {
            AutomationElement? element = this.selector.HoverElement(x, y, color, duration, automationType);
            if (element ==null)
            {
                // 没找到
                return null;
            }
            else
            {
                // 找到
                Models.ElementSelector elementSelector = new Models.ElementSelector(element);
                elementSelector.LoadDetails();
                return elementSelector;
            }
        }

        public Models.ElementSelector? PickUpElement(int x, int y, AutomationType automationType = AutomationType.UIA2)
        {
            AutomationElement? element = this.selector.PickUpElement(x, y, automationType);
            if (element ==null)
            {
                // 没找到
                return null;
            }
            else
            {
                // 找到
                Models.ElementSelector elementSelector = Convert(element);
                return elementSelector;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="elementSelector"></param>
        /// <param name="color"></param>
        /// <param name="duration"></param>
        /// <param name="automationType"></param>
        public void Highlight(Models.ElementSelector elementSelector,
            System.Drawing.Color color,
            TimeSpan duration,
            AutomationType automationType = AutomationType.UIA2)
        {
            List<ConditionBase> conditions = new List<ConditionBase>();
            AutomationBase automationBase = this.selector.GetAutomation(automationType);
            Conditions(elementSelector, conditions, automationBase.ConditionFactory);

            //conditions.Add(new ConditionBase());
            this.selector.Highlight(conditions, color, duration, automationType);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="automationElement"></param>
        /// <returns></returns>
        private static Models.ElementSelector Convert(AutomationElement automationElement)
        {
            Models.ElementSelector elementSelector = new Models.ElementSelector(automationElement);
            elementSelector.LoadDetails();
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
                elementSelector.Parent = Convert(automationElement.Parent);
            }

            return elementSelector;
        }

        /// <summary>
        /// 
        /// </summary>
        private static void Conditions(Models.ElementSelector elementSelector, List<ConditionBase> conditions, ConditionFactory cf)
        {
            List<PropertyCondition> properties = new List<PropertyCondition>();

            string name = "AutomationId";
            if (elementSelector.Properties.Keys.Contains(name) &&
                !string.IsNullOrEmpty((string)elementSelector.Properties[name]))
                properties.Add(cf.ByAutomationId(elementSelector.Properties[name].ToString()));

            name = "Name";
            if (elementSelector.Properties.Keys.Contains(name) &&
                !string.IsNullOrEmpty((string)elementSelector.Properties[name]))
                properties.Add(cf.ByName(elementSelector.Properties[name].ToString()));

            name = "ClassName";
            if (elementSelector.Properties.Keys.Contains(name) &&
                !string.IsNullOrEmpty((string)elementSelector.Properties[name]))
                properties.Add(cf.ByClassName(elementSelector.Properties[name].ToString()));

            name = "ControlType";
            if (elementSelector.Properties.Keys.Contains(name))
                properties.Add(cf.ByControlType((FlaUI.Core.Definitions.ControlType)elementSelector.Properties[name]));

            ConditionBase conditionBase = properties[0];
            for (int i = 1; i < properties.Count; i++)
            {
                conditionBase = conditionBase.And(properties[i]);
            }
            conditions.Insert(0, conditionBase);
            if (elementSelector.Parent != null)
            {
                Conditions(elementSelector.Parent, conditions, cf);
            }
        }

    }
}
