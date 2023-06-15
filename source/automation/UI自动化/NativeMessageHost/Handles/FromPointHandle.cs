using Microsoft.Extensions.Logging;

namespace NativeMessageHost.Handles
{
    internal class FromPointHandle : BaseHandle
    {
        private readonly ILogger<FromPointHandle> logger;
        //private readonly ExtensionsServer extensionsServer;

        public override string Command => "FromPoint";

        public FromPointHandle(ILogger<FromPointHandle> logger)
        {
            this.logger = logger;
            //this.extensionsServer=extensionsServer;
        }

        //public override ProcessMessage Run(ProcessMessage processMessage)
        //{
        //    // 发送数据给插件
        //    var jsonData = new
        //    {
        //        command = processMessage.Command,
        //        Position = new
        //        {
        //            x = processMessage.Position.X,
        //            y = processMessage.Position.Y,
        //        }
        //    };

        //    //var value = this.extensionsServer.Send<dynamic, dynamic>(jsonData);

        //    return processMessage;
        //}
    }
}
