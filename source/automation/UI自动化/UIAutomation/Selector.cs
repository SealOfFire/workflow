using FlaUI.Core;
using FlaUI.Core.AutomationElements;
using FlaUI.Core.Conditions;
using FlaUI.Core.Definitions;
using FlaUI.UIA2;
using FlaUI.UIA3;
using Microsoft.Extensions.Logging;
using System.Drawing;

namespace UIAutomation
{
    /// <summary>
    /// FlaUI 元素选择器
    /// </summary>
    public class Selector
    {
        private readonly ILogger<Selector> logger;

        private readonly AutomationBase uia2Automation;
        private readonly AutomationBase uia3Automation;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="logger"></param>
        public Selector(ILogger<Selector> logger,
            UIA2Automation uia2,
            UIA3Automation uia3)
        {
            this.logger = logger;
            this.uia2Automation = uia2;
            this.uia3Automation = uia3;

            //// 秒
            //AutomationElement rootElement = uia2Automation.GetDesktop();
            //var aa = rootElement.FindAllChildren();
            //int debug = 0;
            //debug++;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="automationType"></param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        internal AutomationBase GetAutomation(AutomationType automationType = AutomationType.UIA2)
        {
            switch (automationType)
            {
                case AutomationType.UIA2:
                    return this.uia2Automation;
                //return (AutomationBase)new UIA2Automation();
                case AutomationType.UIA3:
                    return this.uia3Automation;
                    //return (AutomationBase)new UIA3Automation();
            }
            throw new Exception($"uia类型错误:{automationType}");
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="uiaType"></param>
        /// <returns></returns>
        internal AutomationElement FromPoint(int x, int y, AutomationType automationType = AutomationType.UIA2)
        {
            AutomationBase uia = this.GetAutomation(automationType);
            AutomationElement automationElement = uia.FromPoint(new System.Drawing.Point(x, y));

            //// TODO 判断是否是浏览器中
            //foreach ()
            //{
            //    if (在浏览器中) {
            //        浏览器执行;
            //    }
            //}

            this.logger.LogTrace($"FromPoint - x:[{x}]; y:[{y}], UIAType:[{automationType}], " +
                $"ClassName:[{automationElement.ClassName}]; "+
                $"Name:[{automationElement.Name}]; " +
                $"ControlType:[{automationElement.ControlType}] " +
                $"BoundingRectangle:[{automationElement.BoundingRectangle}]; ");
            return automationElement;
        }

        /// <summary>
        /// 查找元素
        /// TODO 遇到查不到的元素会卡住。也可能不会卡住
        /// </summary>
        /// <param name="aaa"></param>
        /// <returns></returns>
        internal AutomationElement? FindElement(List<ConditionBase> conditions,
            AutomationType automationType = AutomationType.UIA2)
        {
            if (conditions.Count <=0)
            {
                return null;
            }
            else
            {
                AutomationBase automation = this.GetAutomation(automationType);
                AutomationElement rootElement = automation.GetDesktop();

                AutomationElement[] firstResult = rootElement.FindAll(TreeScope.Children, conditions[1]);
                if (firstResult == null)
                {
                    // 没找到元素
                }
                else
                {
                    for (int i = 2; i< conditions.Count; i++)
                    {
                        firstResult= this.FindElement(firstResult, conditions[i]);
                        if (firstResult == null)
                        {
                            // 没找到元素
                            return null;
                        }
                    }
                    if (firstResult.Length >1)
                    {
                        // 找到多个符合条件的元素
                    }
                    else if (firstResult.Length == 0)
                    {
                        // 没找到元素
                    }
                    else
                    {
                        return firstResult[0];
                    }
                }
            }

            return null;
        }

        /// <summary>
        /// 根据条件查找子元素
        /// </summary>
        /// <param name="automationElements"></param>
        /// <param name="condition"></param>
        /// <returns></returns>
        private AutomationElement[] FindElement(AutomationElement[] automationElements, ConditionBase condition)
        {
            List<AutomationElement> result = new List<AutomationElement>();
            foreach (AutomationElement automation in automationElements)
            {
                AutomationElement[] found = automation.FindAll(TreeScope.Children, condition);
                if (found !=null)
                {
                    result.AddRange(found);
                }
            }
            return result.ToArray();
            //return found;
        }

        /// <summary>
        /// 鼠标悬停在元素位置时高亮鼠标下的元素
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="color"></param>
        /// <param name="duration"></param>
        /// <param name="uiaType"></param>
        /// <returns></returns>
        internal AutomationElement? HoverElement(int x, int y, Color color, TimeSpan duration, AutomationType automationType = AutomationType.UIA2)
        {
            this.logger.LogTrace("HoverElement");
            try
            {
                AutomationElement element = this.FromPoint(x, y, automationType);
                // 判断当前是不是在浏览其中

                Task.Run(() => { element.DrawHighlight(false, color, duration); });

                return element;
            }
            catch (System.TimeoutException ex)
            {
                this.logger.LogError($"HoverElement - {ex.StackTrace}");
                return null;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <param name="uiaType"></param>
        /// <returns></returns>
        internal AutomationElement? PickUpElement(int x, int y, AutomationType automationType = AutomationType.UIA2)
        {
            this.logger.LogTrace("PickUpElement");
            try
            {
                AutomationElement automationElement = this.FromPoint(x, y, automationType);

                // 判断当前是不是在浏览其中

                this.logger.LogTrace($"PickUpElement - Name:{automationElement.Name}; ControlType:{automationElement.ControlType}");

                return automationElement;
            }
            catch (System.TimeoutException ex)
            {
                this.logger.LogError($"PickUpElement - {ex.StackTrace}");
                return null;
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="conditions"></param>
        /// <param name="color"></param>
        /// <param name="duration"></param>
        /// <param name="automationType"></param>
        /// <returns></returns>
        internal AutomationElement? Highlight(List<ConditionBase> conditions,
            Color color, TimeSpan duration,
            AutomationType automationType = AutomationType.UIA2)
        {
            AutomationElement? element = this.FindElement(conditions);
            if (element == null)
            {
                return null;
            }
            else
            {
                Task.Run(() => { element.DrawHighlight(false, color, duration); });
                return element;
            }
        }

        ///// <summary>
        ///// 查找元素
        ///// </summary>
        //internal void FindElement()
        //{
        //    Task<string> task = new Task<string>(() =>
        //    {
        //        try
        //        {
        //            Console.WriteLine("task1");
        //            Thread.Sleep(5000);
        //            Console.WriteLine("task2");
        //            int debug = 0;
        //            debug++;
        //        }
        //        catch (Exception e)
        //        {
        //            Console.WriteLine(e.StackTrace);
        //        }
        //        return "完成";
        //    });
        //    task.Start();
        //    Console.WriteLine("out3");
        //    // 等待鼠标识别停止
        //    task.Wait();
        //    // 返回结果
        //    Console.WriteLine(task.Result);

        //    //Console.WriteLine("out4");
        //}


        internal void test1()
        {
            using (var automation = new UIA2Automation())
            {
                AutomationElement desktop = automation.GetDesktop();
                AutomationElement[] children = desktop.FindAllChildren();
                var button1 = desktop.FindFirstDescendant(cf => cf.ByClassName("全部保存"))?.AsButton();
                int debug = 0;
                debug++;
            }
        }

        internal void test2()
        {
            using (var automation = new UIA2Automation())
            {
                //AutomationElement element = automation.FromPoint(new System.Drawing.Point(1227, 70));
                AutomationElement desktop = automation.GetDesktop();

                //var app = FlaUI.Core.Application.Attach(desktop.Properties.ProcessId);
                //var application = app.GetMainWindow(new UIA2Automation());

                ConditionFactory cf = new ConditionFactory(new UIA2PropertyLibrary());

                AutomationElement findElement = desktop.FindFirstDescendant(cf.ByName("Text Editor").And(cf.ByControlType(FlaUI.Core.Definitions.ControlType.Edit)));

                int debug = 0;
                debug++;
            }
        }

        internal void test3()
        {
            using (var automation = new UIA2Automation())
            {
                AutomationElement desktop = automation.GetDesktop();
                //desktop.FindFirst(TreeScope.Descendants, )
                //TreeScope tree = new TreeScope();
                //desktop.FindAt();
            }
        }
    }
}