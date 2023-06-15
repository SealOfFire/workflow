namespace UIAutomation.Models
{
    public class ElementSelector1
    {
        public ElementSelector1? Parent { get; set; }
        public ElementSelector1[]? Children { get; set; }

        /// <summary>
        /// 属性列表
        /// </summary>
        public Dictionary<string, string?> Attributes { get; set; } = new Dictionary<string, string?>();

    }
}
