using GRPCCommon.Protobuf.Common;
using GRPCCommon.Protobuf.NativeMessage;
using UIAutomation.BrowserExtensions;
using UIAutomation.Exceptions;
using UIAutomation.Models;

namespace UIAutomation.Elements
{
    internal class HTMLElement : ElementBase
    {
        private BrowserExtension browserExtension;

        #region 属性

        public string Tag { get; set; }

        public string CacheId { get; set; }

        #endregion

        public HTMLElement(GRPCCommon.Protobuf.Common.Attribute attribute, BrowserExtension browserExtension)
        {
            this.browserExtension = browserExtension;
            this.attribute = attribute;
            this.Tag=attribute.Tag;
            this.CacheId = attribute.CacheId;
        }

        #region 重写方法

        internal override void Highlight(Highlight highlight)
        {
            HighlightResponse response = this.browserExtension.Highlight(this.CacheId, highlight);
            if (response.Success==false)
            {
                throw new BrowserExtensionException(response.Error.Message);
            }
        }

        internal override ElementSelector ToElementSelector()
        {
            throw new NotImplementedException();
        }

        internal override void Click()
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}
