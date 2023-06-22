using FlaUI.Core.AutomationElements;
using GRPCCommon.Protobuf.Common;
using GRPCCommon.Protobuf.NativeMessage;
using Microsoft.Extensions.Logging;

namespace UIAutomation.BrowserExtensions
{
    /// <summary>
    /// 浏览器插件
    /// </summary>
    internal abstract class BrowserExtension
    {
        private readonly ILogger<BrowserExtension> logger;
        protected readonly NativeMessageClient nativeMessageClient;
        protected readonly GrpcNativeMessageClient grpcNativeMessageClient;

        public BrowserExtension(
            ILogger<BrowserExtension> logger,
            NativeMessageClient nativeMessageClient,
            GrpcNativeMessageClient grpcNativeMessageClient)
        {
            this.logger = logger;
            this.nativeMessageClient = nativeMessageClient;
            this.grpcNativeMessageClient = grpcNativeMessageClient;
        }

        /// <summary>
        /// 返回当前的元素是否是html中的元素
        /// </summary>
        /// <param name="automationElement"></param>
        /// <param name="document">html的容器的根元素</param>
        /// <returns></returns>
        internal abstract bool InBrowserDocument(AutomationElement automationElement, out AutomationElement? document);

        /// <summary>
        /// 通过鼠标位置获取元素
        /// </summary>
        /// <param name="request"></param>
        /// <returns></returns>
        internal virtual FromPointResponse FromPoint(FromPointRequest request)
        {
            try
            {
                return this.grpcNativeMessageClient.FromPoint(request);
            }
            catch (Grpc.Core.RpcException e)
            {
                FromPointResponse response = new FromPointResponse();
                response.Success=false;
                response.Error = new Error { Message=e.Message };
                return response;
            }
        }

        /// <summary>
        /// 通过元素属性查找元素
        /// </summary>
        internal virtual FindResponse Find(FindRequest request)
        {
            try
            {
                return this.grpcNativeMessageClient.Find(request);
            }
            catch (Grpc.Core.RpcException e)
            {
                FindResponse response = new FindResponse();
                response.Success=false;
                response.Error = new Error { Message=e.Message };
                return response;
            }
        }

        /// <summary>
        /// 高亮
        /// </summary>
        /// <param name="cacheId"></param>
        internal virtual HighlightResponse Highlight(string cacheId,
            Highlight highlight)
        {
            try
            {
                HighlightRequest request = new HighlightRequest
                {
                    CacheId=cacheId,
                    Highlight =highlight,
                };
                return this.grpcNativeMessageClient.Highlight(request);
            }
            catch (Grpc.Core.RpcException e)
            {
                HighlightResponse response = new HighlightResponse();
                response.Success=false;
                response.Error = new Error { Message=e.Message };
                return response;
            }
        }

    }
}
