using Microsoft.Extensions.Logging;

namespace NativeMessageHost.Handles
{
    internal class FromPointHandle : BaseHandle
    {
        private readonly ILogger<FromPointHandle> logger;

        public override string Command => "fromPoint";

        public FromPointHandle(ILogger<FromPointHandle> logger)
        {
            this.logger = logger;
        }
    }
}
