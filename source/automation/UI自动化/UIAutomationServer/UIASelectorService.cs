using FlaUI.Core.AutomationElements;
using FlaUI.Core.Conditions;
using FlaUI.UIA2;
using FlaUI.UIA3;
using Google.Protobuf;
using Grpc.Core;
using Microsoft.Extensions.Logging;
using System.Drawing;
using UIAutomation.Managers;

namespace UIAutomationServer
{
    internal class UIASelectorService : SelectorService.SelectorServiceBase
    {
        private readonly ILogger<UIASelectorService> logger;
        private GrpcManager elementManager;

        public UIASelectorService(ILogger<UIASelectorService> logger, GrpcManager elementManager)
        {
            this.logger=logger;
            this.elementManager=elementManager;
        }

        /// <summary>
        /// 鼠标悬停在元素上
        /// </summary>
        /// <param name="request"></param>
        /// <param name="context"></param>
        /// <returns></returns>
        public override Task<SelectorReponse> HoverElement(HoverRequest request, ServerCallContext context)
        {
            System.Drawing.Color color = ColorTranslator.FromHtml(request.Color);
            TimeSpan duration = TimeSpan.FromMilliseconds(request.Duration);

            this.elementManager.HoverElement(request.X, request.Y, color, duration, request.Type);
            SelectorReponse reponse = new SelectorReponse();

            return Task.FromResult(reponse);
        }

        /// <summary>
        /// 鼠标选择元素
        /// </summary>
        /// <param name="request"></param>
        /// <param name="context"></param>
        /// <returns></returns>
        public override Task<SelectorReponse> PickUpElement(HoverRequest request, ServerCallContext context)
        {
            UIAutomationServer.Element? selector = this.elementManager.PickUpElement(request.X, request.Y, request.Type);

            SelectorReponse reponse = new SelectorReponse();
            if (selector == null)
            {
                // 没找到元素
                throw new Exception("");
            }
            else
            {
                reponse.Selector=selector;
            }

            return Task.FromResult(reponse);
        }

        /// <summary>
        /// 高亮
        /// </summary>
        /// <param name="request"></param>
        /// <param name="context"></param>
        /// <returns></returns>
        public override Task<SelectorReponse> Highlight(SelectorRequest request, ServerCallContext context)
        {
            // 查找元素
            //ConditionFactory cf;

            // 查找元素的条件
            List<ConditionBase> conditions = new List<ConditionBase>();
            //this.Conditions(request.Element, conditions, cf);
            //this.selector.FindElement();
            System.Drawing.Color color = ColorTranslator.FromHtml(request.Color);
            TimeSpan duration = TimeSpan.FromMilliseconds(request.Duration);

            AutomationElement? result = this.elementManager.Highlight(request.Selector, color, duration, request.Type);

            //AutomationElement? element = null; // this.selector.FindElement(conditions, this.Convert(request.Type));
            //if (element !=null)
            //{
            //    // 高亮
            //    System.Drawing.Color color = ColorTranslator.FromHtml(request.Color);
            //    TimeSpan duration = TimeSpan.FromMilliseconds(request.Duration);
            //    Task.Run(() => { element.DrawHighlight(false, color, duration); });
            //}

            SelectorReponse reponse = new SelectorReponse();
            return Task.FromResult(reponse);
        }



    }

}
