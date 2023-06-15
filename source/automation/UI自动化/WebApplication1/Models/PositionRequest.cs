namespace WebApplication1.Models
{
    /// <summary>
    /// 传入位置请求
    /// </summary>
    public class PositionRequest
    {
        public int X { get; set; }
        public int Y { get; set; }
        public string? Color { get; set; }
        public int? Duration { get; set; }
        public int AutomationType { get; set; }
    }
}
