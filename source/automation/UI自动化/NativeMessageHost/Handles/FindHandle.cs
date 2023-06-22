using Microsoft.Extensions.Logging;

namespace NativeMessageHost.Handles
{
    internal class FindHandle : BaseHandle
    {
        private readonly ILogger<FindHandle> logger;

        public override string Command => "find";

        public FindHandle(ILogger<FindHandle> logger)
        {
            this.logger = logger;
        }
    }
}
