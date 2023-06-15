using System.Drawing;
using UIAutomation.Models;

namespace UIAutomation.Elements
{
    internal class HTMLElement : ElementBase
    {
        #region 属性

        /// <summary>
        /// 属性列表
        /// </summary>
        public Dictionary<string, string?> Attributes { get; set; } = new Dictionary<string, string?>();

        #endregion

        public HTMLElement() { }

        #region 重写方法

        internal override ElementBase[] FindAllChildren(Dictionary<string, object> condition)
        {
            throw new NotImplementedException();
        }

        internal override void Highlight(Color color, TimeSpan duration)
        {
            throw new NotImplementedException();
        }

        internal override ElementSelector ToElementSelector()
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}
