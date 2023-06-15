using System.Drawing;
using UIAutomation.Models;

namespace UIAutomation.Elements
{
    public abstract class ElementBase
    {
        public ElementBase? Parent { get; set; }
        public ElementBase[]? Children { get; set; }

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
        internal abstract void Highlight(Color color, TimeSpan duration);

        /// <summary>
        /// 转换成元素选择器
        /// </summary>
        internal abstract ElementSelector ToElementSelector();
    }
}
