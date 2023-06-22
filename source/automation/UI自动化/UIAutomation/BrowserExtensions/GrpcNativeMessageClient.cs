using Grpc.Core;
using GRPCCommon.Protobuf.NativeMessage;
using Microsoft.Extensions.Logging;

namespace UIAutomation.BrowserExtensions
{
    /// <summary>
    /// 和浏览器插件通信的客户端
    /// </summary>
    public class GrpcNativeMessageClient
    {
        private readonly ILogger<GrpcNativeMessageClient> logger;

        //
        private Channel? channel;
        private NativeMessage.NativeMessageClient? client;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="logger"></param>
        public GrpcNativeMessageClient(ILogger<GrpcNativeMessageClient> logger)
        {
            this.logger = logger;
        }

        internal void Connect(int port)
        {
            this.channel = new Channel($"localhost:{port}", ChannelCredentials.Insecure);
            this.client = new NativeMessage.NativeMessageClient(this.channel);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        internal FromPointResponse FromPoint(FromPointRequest request)
        {
            if (this.client == null)
            {
                throw new Exception("grpc客户端没有创建");
            }
            else
            {
                return this.client.FromPoint(request);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        internal FindResponse Find(FindRequest request)
        {
            if (this.client == null)
            {
                throw new Exception("grpc客户端没有创建");
            }
            else
            {
                return this.client.Find(request);
            }
        }

        /// <summary>
        /// 高亮元素
        /// </summary>
        internal HighlightResponse Highlight(HighlightRequest request)
        {
            if (this.client==null)
            {
                throw new Exception("grpc客户端没有创建");
            }
            else
            {
                return this.client.Highlight(request);
            }
        }

    }
}
