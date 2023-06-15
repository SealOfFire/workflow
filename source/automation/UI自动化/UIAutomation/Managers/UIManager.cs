using FlaUI.Core;
using Microsoft.Extensions.Logging;
using UIAutomation.Elements;

namespace UIAutomation.Managers
{
    public class UIManager
    {
        private readonly ILogger<UIManager> logger;
        private readonly UIAutomation uiAutomation;

        public UIManager(ILogger<UIManager> logger, UIAutomation uiAutomation)
        {
            this.logger = logger;
            this.uiAutomation = uiAutomation;
        }

        public GRPCCommon.HoverResponse Hover(GRPCCommon.HoverRequest request)
        {
            return this.uiAutomation.Hover(request);
        }

        public GRPCCommon.PickUpResponse PickUp(GRPCCommon.PickUpRequest request)
        {
            return this.uiAutomation.PickUp(request);
        }

        public GRPCCommon.HighlightResponse Highlight(GRPCCommon.HighlightRequest request)
        {
            return this.uiAutomation.Highlight(request);
        }

        /// <summary>
        /// 鼠标悬浮
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="color"></param>
        /// <param name="duration"></param>
        /// <param name="automationType"></param>
        public void HoverElement(int x, int y,
            System.Drawing.Color color,
            TimeSpan duration,
            AutomationType automationType = AutomationType.UIA2)
        {
            //
            ElementBase elementBase = this.uiAutomation.FromPoint(x, y, automationType);
            elementBase.Highlight(color, duration);

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="automationType"></param>
        public Models.ElementSelector PickUpElement(int x, int y, AutomationType automationType = AutomationType.UIA2)
        {
            ElementBase elementBase = this.uiAutomation.FromPoint(x, y, automationType);
            return elementBase.ToElementSelector();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="conditions"></param>
        /// <param name="color"></param>
        /// <param name="duration"></param>
        /// <param name="automationType"></param>
        public void Highlight(Models.ElementSelector elementSelector,
            System.Drawing.Color color,
            TimeSpan duration,
            AutomationType automationType = AutomationType.UIA2)
        {
            Dictionary<string, object>[] conditions = new Dictionary<string, object>[1];

            ElementBase? elementBase = this.uiAutomation.FindElement(conditions, automationType);
            if (elementBase != null)
            {
                elementBase.Highlight(color, duration);
            }
        }

    }
}
