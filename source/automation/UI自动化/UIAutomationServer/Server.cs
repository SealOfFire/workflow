using Grpc.Core;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;

namespace UIAutomationServer
{
    internal class Server : Grpc.Core.Server
    {
        private readonly ILogger<Server> logger;
        private readonly IOptions<Options> options;
        private readonly UIASelectorService selectorService;

        public Server(ILogger<Server> logger,
            IOptions<Options> options,
            UIASelectorService selectorService,
            IServiceProvider serviceProvider) : base()
        {
            this.logger = logger;
            this.options = options;
            this.selectorService = selectorService;

            //
            this.logger.LogTrace($"元素识别GRPC服务 -- 监听端口:{this.options.Value.Port}");
            // 
            this.Ports.Add(new ServerPort("localhost", this.options.Value.Port, ServerCredentials.Insecure));
            this.Services.Add(UIAutomationServer.SelectorService.BindService(this.selectorService));
        }
    }
}
