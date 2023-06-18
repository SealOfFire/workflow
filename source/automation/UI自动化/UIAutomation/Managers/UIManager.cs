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
                ElementBase elementBase = this.uiAutomation.FromPoint(request.Position.X, request.Position.Y, 1,
                    (AutomationType)request.AutomationType);

                // 高亮元素
                Color color = ColorTranslator.FromHtml(request.Highlight.Color);
                TimeSpan duration = TimeSpan.FromMilliseconds(request.Highlight.Duration);
                elementBase.Highlight(request.Highlight);

                // 
                HoverResponse response = new HoverResponse
                {
                    Success=true,
                    Attribute = elementBase.Attribute,
                };
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

        public PickUpResponse PickUp(PickUpRequest request)
        {
            try
            {
                ElementBase elementBase = this.uiAutomation.FromPoint(request.Position.X, request.Position.Y, -1,
                   (AutomationType)request.AutomationType);

                // 
                PickUpResponse response = new PickUpResponse
                {
                    Success=true,
                    Attribute = elementBase.Attribute,
                };
                return response;
            }
            catch (Exception ex)
            {
                PickUpResponse response = new PickUpResponse
                {
                    Success=false,
                    Error = new Error { Message= ex.Message }
                };
                return response;
            }
        }

        public HighlightResponse Highlight(HighlightRequest request)
        {
            try
            {
                ElementBase elementBase = this.uiAutomation.Find(request.Attribute, (AutomationType)request.AutomationType);

                // 高亮元素
                Color color = ColorTranslator.FromHtml(request.Highlight.Color);
                TimeSpan duration = TimeSpan.FromMilliseconds(request.Highlight.Duration);
                elementBase.Highlight(request.Highlight);

                // 
                HighlightResponse response = new HighlightResponse
                {
                    Success=true,
                };
                return response;
            }
            catch (Exception ex)
            {
                HighlightResponse response = new HighlightResponse
                {
                    Success=false,
                    Error = new Error { Message= ex.Message }
                };
                return response;
            }
        }

    }
}
