namespace UIAutomation.Ex
{
    /// <summary>
    /// 没有找到元素
    /// </summary>
    public class ElementNotFoundException : Exception
    {
        public ElementNotFoundException() : base("没有找到元素") { }
    }
}
