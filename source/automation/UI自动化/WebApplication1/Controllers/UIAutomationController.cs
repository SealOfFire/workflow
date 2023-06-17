using FlaUI.Core;
using GRPCCommon.Protobuf.UIAutomation;
using Microsoft.AspNetCore.Mvc;
using System.Drawing;
using UIAutomation.Managers;
using UIAutomation.Models;
using WebApplication1.Models;

namespace WebApplication1.Controllers
{
    [ApiController]
    [Route("[controller]/[action]")]
    public class UIAutomationController : ControllerBase
    {
        private readonly ILogger<UIAutomationController> logger;
        private readonly ApiManager webApiManager;
        private readonly UIManager uiManager;

        public UIAutomationController(ILogger<UIAutomationController> logger,
            ApiManager webApiManager,
            UIManager uiManager)
        {
            this.logger = logger;
            this.webApiManager= webApiManager;
            this.uiManager=uiManager;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        [HttpPost]
        public HoverResponse Hover(HoverRequest request)
        {
            return this.uiManager.Hover(request);
        }

        ///// <summary>
        ///// 
        ///// </summary>
        ///// <param name="request"></param>
        ///// <returns></returns>
        //[HttpPost]
        //public PickUpResponse PickUp(.Protobu.PickUpRequest request)
        //{
        //    return this.uiManager.PickUp(request);
        //}

        ///// <summary>
        ///// 
        ///// </summary>
        ///// <param name="request"></param>
        ///// <returns></returns>
        //[HttpPost]
        //public HighlightResponse Highlight(GRPCCommon.Protobuf.HighlightRequest request)
        //{
        //    return this.uiManager.Highlight(request);
        //}

        /// <summary>
        /// 
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        [HttpPost]
        public SelectorResponse HoverElement(PositionRequest request)
        {
            Color color = ColorTranslator.FromHtml(request.Color);
            TimeSpan duration = TimeSpan.FromMilliseconds(request.Duration.Value);
            AutomationType automationType = request.AutomationType == 3 ? AutomationType.UIA3 : AutomationType.UIA2;

            this.uiManager.HoverElement(request.X, request.Y, color, duration, automationType);
            return new SelectorResponse { Selector=null };

            //ElementSelector? elementSelector = this.webApiManager.HoverElement(request.X, request.Y, color, duration, automationType);
            //if (elementSelector == null)
            //{
            //    return new SelectorResponse { Selector=null };
            //}
            //else
            //{
            //    return new SelectorResponse { Selector = elementSelector };
            //}
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        [HttpPost]
        public SelectorResponse PickUpElement(PositionRequest request)
        {
            AutomationType automationType = request.AutomationType == 3 ? AutomationType.UIA3 : AutomationType.UIA2;
            ElementSelector? elementSelector = this.webApiManager.PickUpElement(request.X, request.Y, automationType);
            if (elementSelector == null)
            {
                return new SelectorResponse { Selector=null };
            }
            else
            {
                return new SelectorResponse { Selector = elementSelector };
            }
        }

        [HttpPost("aaaa")]
        public Object Highlight(SelectorRequest request)
        {
            Color color = ColorTranslator.FromHtml(request.Color);
            TimeSpan duration = TimeSpan.FromMilliseconds(request.Duration.Value);

            UIAutomation.Models.ElementSelector elementSelector1 = new UIAutomation.Models.ElementSelector();
            elementSelector1.Properties.Add("ClassName", "#32769");
            elementSelector1.Properties.Add("ControlType", 21);

            ElementSelector elementSelector2 = new ElementSelector();
            elementSelector2.Properties.Add("Name", "UI自动化 (正在调试) - Microsoft Visual Studio");
            elementSelector2.Properties.Add("ControlType", 41);
            elementSelector2.Parent = elementSelector1;

            ElementSelector elementSelector3 = new ElementSelector();
            elementSelector3.Properties.Add("ClassName", "DockRoot2");
            elementSelector3.Properties.Add("ControlType", 21);
            elementSelector3.Parent = elementSelector2;

            ElementSelector elementSelector4 = new ElementSelector();
            elementSelector4.Properties.Add("ClassName", "DocumentGroup");
            elementSelector4.Properties.Add("ControlType", 31);
            elementSelector4.Parent = elementSelector3;

            AutomationType automationType = request.AutomationType == 3 ? AutomationType.UIA3 : AutomationType.UIA2;
            this.webApiManager.Highlight(elementSelector4, color, duration, automationType);
            return new { Value = "aa" };
        }
    }
}
