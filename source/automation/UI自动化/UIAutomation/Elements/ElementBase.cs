using GRPCCommon.Protobuf.Common;
using UIAutomation.Models;

namespace UIAutomation.Elements
{
    public abstract class ElementBase
    {
        #region 属性

        public ElementBase? Parent { get; set; }
        public ElementBase[]? Children { get; set; }

        #endregion

        /// <summary>
        /// 不能通过new创建
        /// </summary>
        protected ElementBase() { }

        /// <summary>
        /// 查找符合条件的子元素
        /// </summary>
        /// <param name="condition"></param>
        /// <returns></returns>
        internal abstract ElementBase[] FindAllChildren(Dictionary<string, object> condition);

        /// <summary>
        /// 高亮当前元素
        /// </summary>
        /// <param name="color"></param>
        /// <param name="duration"></param>
        internal abstract void Highlight(Highlight highlight);

        /// <summary>
        /// 鼠标点击
        /// </summary>
        internal abstract void Click();

        /// <summary>
        /// 转换成元素选择器
        /// </summary>
        internal abstract ElementSelector ToElementSelector();
    }
}
