using GRPCCommon.Protobuf.UIAutomation;
using Microsoft.AspNetCore.Mvc;
using UIAutomation.Managers;

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


        [HttpPost]
        public PickUpResponse PickUp(PickUpRequest request)
        {
            return this.uiManager.PickUp(request);
        }

        [HttpPost]
        public HighlightResponse Highlight(HighlightRequest request)
        {
            return this.uiManager.Highlight(request);
        }
    }
}
