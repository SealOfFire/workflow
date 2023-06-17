using GRPCCommon.Protobuf.Common;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json.Linq;

namespace NativeMessageHost.Handles
{
    internal class HandleManager
    {
        private readonly ILogger<HandleManager> logger;
        private readonly IServiceProvider serviceProvider;
        private readonly Dictionary<string, BaseHandle> handles;

        public Dictionary<string, BaseHandle> Handles { get => this.handles; }

        public HandleManager(ILogger<HandleManager> logger,
             IServiceProvider serviceProvider)
        {
            this.logger = logger;
            this.serviceProvider = serviceProvider;

            // 把自动注入的类添加到处理列表里面
            IEnumerable<BaseHandle> baseHandles = this.serviceProvider.GetServices<BaseHandle>();

            this.handles = new Dictionary<string, BaseHandle>();
            foreach (var baseHandle in baseHandles)
            {
                this.handles.Add(baseHandle.Command, baseHandle);
            }

        }

        /// <summary>
        /// 是否有处理命令的对象
        /// </summary>
        /// <param name="command"></param>
        /// <returns></returns>
        public bool HasHandle(string command, out Error? error)
        {
            error =null;
            if (this.handles.Keys.Contains(command))
            {
                return true;
            }
            error = new Error { Message=$"浏览器插件native中没有注册处理[{command}]的类" };
            return false;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="processMessage"></param>
        /// <returns></returns>
        /// <exception cref="MessageException"></exception>
        public byte[] ToConsole(Request request)
        {
            if (this.handles.Keys.Contains(request.Command))
            {
                return this.handles[request.Command].ToConsole(request);
            }
            else
            {
                this.logger.LogError($"处理ToConsole[{request.Command}]的handle不存在");
                return new byte[0];
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="command"></param>
        /// <param name="value"></param>
        /// <param name="error"></param>
        /// <returns></returns>
        public byte[] ToConsole<T>(string command, T value, out Error? error)
        {
            error=null;
            if (this.handles.Keys.Contains(command))
            {
                return this.handles[command].ToConsole<T>(value);
            }
            else
            {
                error = new Error { Message =  $"处理ToConsole[{command}]的handle不存在" };
                this.logger.LogError(error.Message);
                return new byte[0];
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="processMessage"></param>
        /// <returns></returns>
        /// <exception cref="MessageException"></exception>
        //public GRPCCommon.Response ToNamedPip(ProcessMessage value)
        //{
        //    //string command = ((IDictionary<string, object>)value)["Command"].ToString();
        //    if (this.handles.Keys.Contains(value.Command))
        //    {
        //        return this.handles[value.Command].ToNamedPipe(value);
        //    }
        //    else
        //    {
        //        ProcessMessage result = new ProcessMessage();
        //        result.Error = new Error { Message =$"处理ToNamedPip[{value.Command}]的handle不存在" };
        //        this.logger.LogError(result.Error.Message);
        //        return result;
        //    }
        //}

        public T? ToNamedPip<T>(JObject value, out Error? error) where T : class
        {
            error=null;
            string? command = value.GetValue("Command")?.Value<string>();
            if (string.IsNullOrEmpty(command))
            {
                error= new Error { Message ="处理ToNamedPip属性值[Command]不存在" };
                this.logger.LogError(error.Message);
                return null;
            }
            else
            {
                if (this.handles.Keys.Contains(command))
                {
                    return this.handles[command].ToNamedPipe<T>(value);
                }
                else
                {
                    error= new Error { Message =$"处理ToNamedPip[{command}]的handle不存在" };
                    this.logger.LogError(error.Message);
                    return null;
                }
            }
        }

    }
}
