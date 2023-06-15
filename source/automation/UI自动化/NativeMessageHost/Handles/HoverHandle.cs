using Microsoft.Extensions.Logging;

namespace NativeMessageHost.Handles
{
    /// <summary>
    /// 鼠标悬浮的处理
    /// </summary>
    internal class HoverHandle : BaseHandle
    {
        private readonly ILogger<HoverHandle> logger;

        public override string Command => "hover";

        public HoverHandle(ILogger<HoverHandle> logger)
        {
            this.logger = logger;
        }

    }
}
