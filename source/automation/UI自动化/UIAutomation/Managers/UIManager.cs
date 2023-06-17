using FlaUI.Core;
using GRPCCommon.Protobuf.Common;
using GRPCCommon.Protobuf.UIAutomation;
using Microsoft.Extensions.Logging;
using System.Drawing;
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

        public HoverResponse Hover(HoverRequest request)
        {
            try
            {
                // 查找元素
                ElementBase elementBase = this.uiAutomation.通过鼠标位置获取元素(request.Position.X, request.Position.Y,
                    (AutomationType)request.AutomationType);

                // 高亮元素
                Color color = ColorTranslator.FromHtml(request.Highlight.Color);
                TimeSpan duration = TimeSpan.FromMilliseconds(request.Highlight.Duration);
                elementBase.Highlight(request.Highlight);

                // 
                HoverResponse response = new HoverResponse { Success=true };
                return response;
            }
            catch (Exception ex)
            {
                HoverResponse response = new HoverResponse
                {
                    Success=false,
                    Error = new Error { Message= ex.Message }
                };
                return response;
            }
        }

        //public GRPCCommon.Protobuf.PickUpResponse PickUp(GRPCCommon.Protobuf.PickUpRequest request)
        //{
        //    return this.uiAutomation.PickUp(request);
        //}

        //public GRPCCommon.Protobuf.HighlightResponse Highlight(GRPCCommon.Protobuf.HighlightRequest request)
        //{
        //    return this.uiAutomation.Highlight(request);
        //}

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
            //elementBase.Highlight(color, duration);

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
            throw new NotImplementedException();
        }

    }
}
