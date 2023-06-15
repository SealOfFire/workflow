using Microsoft.Extensions.Logging;

namespace NativeMessageHost.Handles
{
    /// <summary>
    /// 鼠标悬浮的处理
    /// </summary>
    internal class PickUpHandle : BaseHandle
    {
        private readonly ILogger<PickUpHandle> logger;

        public override string Command => "pickUp";

        public PickUpHandle(ILogger<PickUpHandle> logger)
        {
            this.logger = logger;
        }

    }
}
