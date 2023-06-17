using Microsoft.Extensions.Logging;

namespace NativeMessageHost.Handles
{
    internal class HighlightHandle : BaseHandle
    {
        private readonly ILogger<HighlightHandle> logger;

        public override string Command => "highlight";

        public HighlightHandle(ILogger<HighlightHandle> logger)
        {
            this.logger = logger;
        }
    }
}
