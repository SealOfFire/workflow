using Grpc.Core;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;

namespace NativeMessageHost
{
    internal class GrpcService : Grpc.Core.Server
    {
        private readonly ILogger<GrpcService> logger;
        private readonly IOptions<Options> options;
        //private readonly UIAutomation uiAutomation;
        //private readonly NativeMessageService service;

        public GrpcService(ILogger<GrpcService> logger,
          IOptions<Options> options,
          NativeMessageService service) : base()
        {
            this.logger = logger;
            this.options = options;
            //this.uiAutomation = uiAutomation;

            //
            this.logger.LogTrace($"grpc服务 -- 监听端口:{this.options.Value.Port}");
            // 
            this.Ports.Add(new ServerPort("localhost", this.options.Value.Port, ServerCredentials.Insecure));
            //GRPCCommon.UIAutomation.BindService(this.uiAutomation);
            //this.Services.Add(GRPCCommon.Protobuf.UIAutomation.UIAutomation.BindService(this.uiAutomation));
            this.Services.Add(GRPCCommon.Protobuf.NativeMessage.NativeMessage.BindService(service));
        }


    }
}
