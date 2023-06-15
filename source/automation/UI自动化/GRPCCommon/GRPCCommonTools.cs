using Google.Protobuf;
using ProcessCommunication;

namespace GRPCCommon
{
    public class GRPCCommonTools
    {

        /// <summary>
        /// 
        /// </summary>
        /// <param name="processMessage"></param>
        /// <returns></returns>
        public static byte[] ToBytes(ProcessMessage processMessage)
        {
            byte[] buffer = processMessage.ToByteArray();
            byte[] lengthBuffer = BitConverter.GetBytes(buffer.Length);

            byte[] data = new byte[buffer.Length+4];
            lengthBuffer.CopyTo(data, 0);
            buffer.CopyTo(data, 4);
            return data;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="processMessage"></param>
        /// <returns></returns>
        public static byte[] ToBytes(GRPCCommon.Request request)
        {
            byte[] buffer = request.ToByteArray();
            byte[] lengthBuffer = BitConverter.GetBytes(buffer.Length);

            byte[] data = new byte[buffer.Length+4];
            lengthBuffer.CopyTo(data, 0);
            buffer.CopyTo(data, 4);
            return data;
        }

        /// <summary>
        /// grpc对象转换成字节数组
        /// </summary>
        /// <param name="stream"></param>
        /// <param name="processMessage"></param>
        public static void Send(Stream stream, ProcessMessage processMessage)
        {
            byte[] buffer = processMessage.ToByteArray();
            byte[] lengthBuffer = BitConverter.GetBytes(buffer.Length);

            // 发送数据长度
            stream.Write(lengthBuffer, 0, lengthBuffer.Length);

            // 发送数据本身
            stream.Write(buffer, 0, buffer.Length);
        }

        public static void Send(Stream stream, GRPCCommon.Request request)
        {
            byte[] buffer = request.ToByteArray();
            byte[] lengthBuffer = BitConverter.GetBytes(buffer.Length);

            // 发送数据长度
            stream.Write(lengthBuffer, 0, lengthBuffer.Length);

            // 发送数据本身
            stream.Write(buffer, 0, buffer.Length);
        }

        /// <summary>
        /// 接收的字节数组转换成grpc对象
        /// </summary>
        /// <param name="stream"></param>
        /// <returns></returns>
        public static ProcessMessage? Read2(Stream stream)
        {
            // 接收长度
            byte[] lengthBuffer = new byte[4];
            stream.Read(lengthBuffer, 0, 4); // read会阻塞线程等待输出传入

            int length = BitConverter.ToInt32(lengthBuffer, 0);

            if (length >0)
            {
                // 接收数据本身
                byte[] dataBuffer = new byte[length];
                stream.Read(dataBuffer, 0, length);

                ProcessMessage processMessage = ProcessMessage.Parser.ParseFrom(dataBuffer);
                return processMessage;
            }
            else
            {
                return null;
            }
        }

        public static GRPCCommon.Response? Read(Stream stream)
        {
            // 接收长度
            byte[] lengthBuffer = new byte[4];
            stream.Read(lengthBuffer, 0, 4); // read会阻塞线程等待输出传入

            int length = BitConverter.ToInt32(lengthBuffer, 0);

            if (length >0)
            {
                // 接收数据本身
                byte[] dataBuffer = new byte[length];
                stream.Read(dataBuffer, 0, length);

                GRPCCommon.Response response = GRPCCommon.Response.Parser.ParseFrom(dataBuffer);
                return response;
            }
            else
            {
                return null;
            }
        }

    }
}
