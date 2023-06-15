using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using ProcessCommunication;
using System.Text;

namespace NativeMessageHost.Handles
{
    internal abstract class BaseHandle
    {
        /// <summary>
        /// 要执行的命令
        /// </summary>
        public virtual string Command { get; } = string.Empty;

        /// <summary>
        /// 执行命令的具体操作
        /// </summary>
        /// <param name="processMessage"></param>
        /// <returns></returns>
        //public abstract ProcessMessage Run(ProcessMessage processMessage);

        //public abstract Task RunAsync(ProcessMessage processMessage);

        public virtual byte[] ToConsole(ProcessMessage processMessage)
        {
            //JsonSerializerOptions options = new()
            //{
            //    DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull
            //};
            //string json = JsonSerializer.Serialize(processMessage, options);


            JsonSerializerSettings jSetting = new JsonSerializerSettings { NullValueHandling = NullValueHandling.Ignore };
            String json = JsonConvert.SerializeObject(processMessage, jSetting);

            byte[] buffer = Encoding.UTF8.GetBytes(json);

            byte[] lengthBuffer = BitConverter.GetBytes(buffer.Length);
            byte[] result = new byte[buffer.Length+lengthBuffer.Length];

            lengthBuffer.CopyTo(result, 0);
            buffer.CopyTo(result, lengthBuffer.Length);

            return result;
        }

        public virtual byte[] ToConsole<T>(T value)
        {
            JsonSerializerSettings jSetting = new JsonSerializerSettings { NullValueHandling = NullValueHandling.Ignore };
            string json = JsonConvert.SerializeObject(value, jSetting);

            byte[] buffer = Encoding.UTF8.GetBytes(json);

            byte[] lengthBuffer = BitConverter.GetBytes(buffer.Length);
            byte[] result = new byte[buffer.Length+lengthBuffer.Length];

            lengthBuffer.CopyTo(result, 0);
            buffer.CopyTo(result, lengthBuffer.Length);

            return result;
        }

        public virtual GRPCCommon.Response ToNamedPipe(JObject json)
        {
            //GRPCCommon.Response? response = System.Text.Json.JsonSerializer.Deserialize<GRPCCommon.Response>(json);
            GRPCCommon.Response? response = json.ToObject<GRPCCommon.Response>();
            return response;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="json"></param>
        /// <returns></returns>
        public virtual T? ToNamedPipe<T>(JObject json)
        {
            T? result = json.ToObject<T>();
            //T? result = JsonConvert.DeserializeObject<T>(json);
            return result;
        }
    }
}
