using Grpc.Core;
using Microsoft.Extensions.Logging;

namespace UIAutomation.BrowserExtensions
{
    public class GrpcNativeMessageClient
    {
        private readonly ILogger<GrpcNativeMessageClient> logger;

        //
        private Channel? channel;
        private GRPCCommon.UIAutomation.UIAutomationClient? client;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="logger"></param>
        public GrpcNativeMessageClient(ILogger<GrpcNativeMessageClient> logger)
        {
            this.logger = logger;
        }

        public void Connect(int port)
        {
            this.channel = new Channel($"localhost:{port}", ChannelCredentials.Insecure);
            this.client = new GRPCCommon.UIAutomation.UIAutomationClient(this.channel);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        public GRPCCommon.HoverResponse Hover(GRPCCommon.HoverRequest request)
        {
            if (this.client == null)
            {
                throw new Exception("grpc客户端没有创建");
            }
            else
            {
                return this.client.Hover(request);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        public GRPCCommon.PickUpResponse PickUp(GRPCCommon.PickUpRequest request)
        {
            if (this.client == null)
            {
                throw new Exception("grpc客户端没有创建");
            }
            else
            {
                return this.client.PickUp(request);
            }
        }

    }
}
