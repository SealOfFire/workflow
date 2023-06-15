﻿using FlaUI.Core.AutomationElements;
using FlaUI.Core.Exceptions;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UIAutomation.Elements;

namespace UIAutomation.BrowserExtensions
{
    public class EdgeExtension : BrowserExtension
    {
        public EdgeExtension(ILogger<BrowserExtension> logger,
            NativeMessageClient nativeMessageClient,
             GrpcNativeMessageClient grpcNativeMessageClient)
            : base(logger, nativeMessageClient, grpcNativeMessageClient)
        {
            this.grpcNativeMessageClient.Connect(50002);
        }

        internal override ElementBase[] FindElement()
        {
            throw new NotImplementedException();
        }

        internal override ElementBase FromPoint(int x, int y)
        {
            int debug = 0;
            debug++;
            throw new NotImplementedException();
        }

        internal override bool InBrowserDocument(AutomationElement automationElement, out AutomationElement? document)
        {
            // 向上查看父级是否在浏览器中。如果鼠标是浏览器中的html元素，向上一直找到浏览器的根。
            // 如果选中的是浏览器的html容器，没法再进去了，同样通过查看父级获取是否在浏览器中
            bool inDocument = false;
            document=null;
            if (automationElement.Parent !=null)
            {
                AutomationElement parent = automationElement.Parent;
                while (true)
                {
                    try
                    {
                        if (parent.ControlType == FlaUI.Core.Definitions.ControlType.Document)
                        {
                            // 鼠标在文档部分
                            inDocument = true;
                            document = parent;
                        }
                        if (parent.ClassName=="Chrome_WidgetWin_1"
                            && parent.ControlType == FlaUI.Core.Definitions.ControlType.Window)
                        {
                            // chrome浏览器
                            return true && inDocument;
                        }
                        else
                        {
                            if (parent.Parent !=null)
                                parent = parent.Parent;
                            else
                                return false;
                        }
                    }
                    catch (PropertyNotSupportedException)
                    {
                        if (parent.Parent !=null)
                            parent = parent.Parent;
                        else
                            return false;
                    }
                }
            }

            return false;
        }
    }
}
