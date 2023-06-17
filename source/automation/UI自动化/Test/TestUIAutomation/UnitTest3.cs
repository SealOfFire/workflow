using GRPCCommon.Protobuf;
using GRPCCommon.Protobuf.Common;
using UIAutomation.BrowserExtensions;

namespace TestUIAutomation
{
    /// <summary>
    /// grpc≤‚ ‘
    /// </summary>
    public class UnitTest3
    {
        private readonly GrpcNativeMessageClient grpcClient;

        public UnitTest3(GrpcNativeMessageClient grpcClient)
        {
            this.grpcClient = grpcClient;
        }

        [Fact]
        public void Test1()
        {
            this.grpcClient.Connect(50001);

            //HoverRequest request1 = new HoverRequest
            //{
            //    Id= Guid.NewGuid().ToString(),
            //    MillisecondsTimeout=2000
            //};
            //request1.Position = new Position { X=11, Y=22 };
            //request1.Highlight = new Highlight { Color="#FF0000", Duration=2000 };

            ////this.nativeMessageClient.Write(processMessage);
            //HoverResponse? result1 = this.grpcClient.Hover(request1);

            //HoverRequest request2 = new HoverRequest
            //{
            //    Id= Guid.NewGuid().ToString(),
            //    MillisecondsTimeout=2000
            //};
            //request2.Position = new Position { X=33, Y=44 };
            //request2.Highlight = new Highlight { Color="#FF0000", Duration=2000 };
            //HoverResponse? result2 = this.grpcClient.Hover(request2);

            int debug = 0;
            debug++;

        }

    }
}