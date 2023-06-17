using FlaUI.Core.AutomationElements;
using GRPCCommon.Protobuf.Common;
using GRPCCommon.Protobuf.NativeMessage;
using Microsoft.Extensions.Logging;
using System.IO.Pipes;
using UIAutomation.Elements;

namespace UIAutomation.BrowserExtensions
{
    public abstract class BrowserExtension
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

        internal abstract ElementBase FromPoint(int x, int y);

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

        ///// <summary>
        ///// 高亮元素
        ///// </summary>
        ///// <param name="request"></param>
        ///// <returns></returns>
        //internal virtual GRPCCommon.Protobuf.HoverResponse Hover(GRPCCommon.Protobuf.HoverRequest request)
        //{
        //    try
        //    {
        //        return this.grpcNativeMessageClient.Hover(request);
        //    }
        //    catch (Grpc.Core.RpcException e)
        //    {
        //        GRPCCommon.Protobuf.HoverResponse response = new GRPCCommon.Protobuf.HoverResponse();
        //        response.Success=false;
        //        response.Error = new Error { Message=e.Message };
        //        return response;
        //    }
        //}

        ///// <summary>
        ///// 选取元素
        ///// </summary>
        ///// <param name="request"></param>
        ///// <returns></returns>
        //internal virtual GRPCCommon.Protobuf.PickUpResponse PickUp(GRPCCommon.Protobuf.PickUpRequest request)
        //{
        //    try
        //    {
        //        return this.grpcNativeMessageClient.PickUp(request);
        //    }
        //    catch (Grpc.Core.RpcException e)
        //    {
        //        GRPCCommon.Protobuf.PickUpResponse response = new GRPCCommon.Protobuf.PickUpResponse();
        //        response.Success=false;
        //        response.Error = new Error { Message=e.Message };
        //        return response;
        //    }
        //}

        internal abstract ElementBase[] FindElement();

        internal void Test()
        {
            using (NamedPipeClientStream pipeClient = new NamedPipeClientStream(".", "testpipe", PipeDirection.InOut))
            {

                // Connect to the pipe or wait until the pipe is available.
                Console.Write("Attempting to connect to pipe...");
                pipeClient.Connect();

                Console.WriteLine("Connected to pipe.");
                Console.WriteLine("There are currently {0} pipe server instances open.", pipeClient.NumberOfServerInstances);
                using (StreamReader sr = new StreamReader(pipeClient))
                {
                    // Display the read text to the console
                    string temp;
                    while ((temp = sr.ReadLine()) != null)
                    {
                        Console.WriteLine("Received from server: {0}", temp);
                    }
                }
            }
            Console.Write("Press Enter to continue...");
            Console.ReadLine();
        }
    }
}
