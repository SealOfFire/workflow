using GRPCCommon.Protobuf.Common;
using UIAutomation.Models;

namespace UIAutomation.Elements
{
    public abstract class ElementBase
    {
        /// <summary>
        /// 元素属性列表
        /// </summary>
        protected GRPCCommon.Protobuf.Common.Attribute attribute;

        #region 属性

        internal ElementBase? Parent { get; set; }
        internal ElementBase[]? Children { get; set; }

        internal GRPCCommon.Protobuf.Common.Attribute Attribute { get { return this.attribute; } }

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
        //internal abstract ElementBase[] FindAllChildren(Dictionary<string, object> condition);

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
