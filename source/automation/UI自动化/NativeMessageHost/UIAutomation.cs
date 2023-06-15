using Grpc.Core;
using GRPCCommon;
using Microsoft.Extensions.Logging;
using NativeMessageHost.Handles;
using Newtonsoft.Json.Linq;
using System.Reflection;

namespace NativeMessageHost
{
    internal class UIAutomation : GRPCCommon.UIAutomation.UIAutomationBase
    {
        private readonly ILogger<UIAutomation> logger;
        private readonly JsonDictionary jsonDictionary;
        private readonly HandleManager handleManager;
        private readonly ConsoleBackgroundTask consoleBackgroundTask;

        public UIAutomation(ILogger<UIAutomation> logger,
            JsonDictionary jsonDictionary,
            HandleManager handleManager,
            ConsoleBackgroundTask consoleBackgroundTask)
        {
            this.logger = logger;
            this.jsonDictionary=jsonDictionary;
            this.handleManager=handleManager;
            this.consoleBackgroundTask=consoleBackgroundTask;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="TIn"></typeparam>
        /// <typeparam name="TOut"></typeparam>
        /// <param name="command"></param>
        /// <param name="request"></param>
        /// <param name="error"></param>
        /// <returns></returns>
        public TOut Common<TIn, TOut>(string command, TIn request, out Error? error) where TOut : class, new()
        {
            string id = Guid.NewGuid().ToString();
            int millisecondsTimeout = 2000;
            TOut? response = new TOut();
            error=null;

            Type type = typeof(TIn);
            PropertyInfo? piId = type.GetProperty("Id");
            if (piId !=null)
            {
                object? val = piId.GetValue(request);
                if (val == null)
                {
                    piId.SetValue(request, id);
                }
                else if (string.IsNullOrEmpty((string)val))
                {
                    piId.SetValue(request, id);
                }
                else
                {
                    id = (string)val;
                }
            }
            //
            PropertyInfo? piTimeout = type.GetProperty("MillisecondsTimeout");
            if (piTimeout !=null)
            {
                object? val = piTimeout.GetValue(request);
                if (val == null)
                {
                    piTimeout.SetValue(request, millisecondsTimeout);
                }
                else if ((int)val == 0)
                {
                    piTimeout.SetValue(request, millisecondsTimeout);
                }
                else
                {
                    millisecondsTimeout =(int)val;
                }
            }
            //
            PropertyInfo? piCommand = type.GetProperty("Command");
            if (piCommand !=null)
            {
                piCommand.SetValue(request, command);
            }

            byte[] consoleBuffer = this.handleManager.ToConsole(command, request, out error);
            if (consoleBuffer.Length == 0)
            {
                //response.Error=error;
            }
            else
            {
                // 写道控制台
                this.consoleBackgroundTask.Write(consoleBuffer);

                // 等待控制台返回
                JObject json = new JObject();
                bool isTimeout = Task.Run(() =>
                {
                    while (this.jsonDictionary.ContainsKey(id) == false) { }
                    json = this.jsonDictionary[id];
                    this.jsonDictionary.Remove(id);
                }).Wait(millisecondsTimeout);

                if (isTimeout)
                {
                    // 回写回管道
                    this.logger.LogWarning($"grpc {command} 返回[{json}]");
                    response =  this.handleManager.ToNamedPip<TOut>(json, out error);
                    if (response==null)
                    {
                        response = new TOut();
                        //response.Error = error;
                    }
                }
                else
                {
                    // 处理超时，返回错误信息 ProcessMessage
                    string message = $"grpc {command} [{millisecondsTimeout}]毫秒内，没有从控制台获取到返回的任务{id}";
                    this.logger.LogWarning(message);
                    error = new Error { Message=message };
                    //response.Error= error;
                }
            }
            return response;
        }

        /// <summary>
        /// 鼠标高亮
        /// </summary>
        /// <param name="request"></param>
        /// <param name="context"></param>
        /// <returns></returns>
        public override Task<HoverResponse> Hover(HoverRequest request, ServerCallContext context)
        {
            this.logger.LogWarning($"grpc Hover");
            string command = "hover";

            Error? error;

            HoverResponse response = this.Common<HoverRequest, HoverResponse>(command, request, out error);
            if (error !=null)
            {
                response.Error = error;
            }

            return Task.FromResult(response);
        }

        public override Task<HighlightResponse> Highlight(HighlightRequest request, ServerCallContext context)
        {
            this.logger.LogWarning($"grpc Highlight");
            string command = "highlight";

            Error? error;

            HighlightResponse response = this.Common<HighlightRequest, HighlightResponse>(command, request, out error);
            if (error !=null)
            {
                response.Error = error;
            }

            return Task.FromResult(response);
        }

        public override Task<PickUpResponse> PickUp(PickUpRequest request, ServerCallContext context)
        {
            this.logger.LogWarning($"grpc PickUp");
            string command = "pickUp";

            Error? error;

            PickUpResponse response = this.Common<PickUpRequest, PickUpResponse>(command, request, out error);
            if (error !=null)
            {
                response.Error = error;
            }

            return Task.FromResult(response);
        }
    }
}
