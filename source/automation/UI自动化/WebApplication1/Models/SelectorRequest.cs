namespace WebApplication1.Models
{
    /// <summary>
    /// 选择器的请求
    /// </summary>
    public class SelectorRequest
    {
        public UIAutomation.Models.ElementSelector? Selector { get; set; }
        public string? Color { get; set; }
        public int? Duration { get; set; }
        public int AutomationType { get; set; }
    }
}
