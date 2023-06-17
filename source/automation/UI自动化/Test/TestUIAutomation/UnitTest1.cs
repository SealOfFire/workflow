using FlaUI.Core;
using GRPCCommon.Protobuf;
using GRPCCommon.Protobuf.Common;
using Newtonsoft.Json;
using System.Drawing;
using System.Text.Json;
using System.Text.Json.Serialization;
using UIAutomation.BrowserExtensions;
using UIAutomation.Managers;

namespace TestUIAutomation
{
    public class UnitTest1
    {
        private readonly UIManager uIManager;
        private readonly NativeMessageClient nativeMessageClient;

        public UnitTest1(UIManager uIManager, NativeMessageClient nativeMessageClient)
        {
            this.uIManager = uIManager;
            this.nativeMessageClient=nativeMessageClient;
        }

        [Theory]
        [InlineData(1740, 458, "#FF0000", 20000, AutomationType.UIA2)]
        public void Test1(int x, int y, string color, int duration, AutomationType automationType)
        {
            Color color1 = ColorTranslator.FromHtml(color);
            TimeSpan duration1 = TimeSpan.FromMilliseconds(duration);
            this.uIManager.HoverElement(x, y, color1, duration1, automationType);

        }

        [Fact]
        public void Test2()
        {
            ////NativeMessageClient nativeMessageClient = new NativeMessageClient();
            //this.nativeMessageClient.Connect("NativeMessageHost2");
            ////tasks[0] = nativeMessageClient.Connect();
            ////tasks[0].Start();

            ////Thread.Sleep(2000);

            //ProcessMessage processMessage = new ProcessMessage { Id= Guid.NewGuid().ToString(), Success=false, Command = "hover" };
            //processMessage.Position = new Position { X=11, Y=22 };
            //processMessage.Highlight = new Highlight { Color="#FF0000", Duration=2000 };
            ////this.nativeMessageClient.Write(processMessage);
            //ProcessMessage? result1 = this.nativeMessageClient.Send(processMessage);
            ////ProcessMessage result1 = this.nativeMessageClient.Send("", processMessage);

            //ProcessMessage processMessage2 = new ProcessMessage { Id= Guid.NewGuid().ToString(), Command = "hover" };
            //processMessage2.Position = new Position { X=33, Y=44 };
            //processMessage2.Highlight = new Highlight { Color="#FF0000", Duration=2000 };
            //ProcessMessage? result2 = this.nativeMessageClient.Send(processMessage2);

            ////this.nativeMessageClient.Close();
            //int debug = 0;
            //debug++;

        }

        [Fact]
        public void Test3()
        {
            //ProcessMessage processMessage = new ProcessMessage { Id= Guid.NewGuid().ToString(), Success=false, Command = "hover" };
            //processMessage.Position = new Position { X=11, Y=22 };
            //processMessage.Highlight = new Highlight { Color="#FF0000", Duration=2000 };
            //processMessage.Attribute = new ProcessCommunication.Attribute();
            //processMessage.Attribute.Values.Add("tag", "div");
            //processMessage.Attribute.Values.Add("class", "ddd");

            //JsonSerializerOptions options = new()
            //{
            //    DefaultIgnoreCondition = JsonIgnoreCondition.WhenWritingNull
            //};
            //string json = System.Text.Json.JsonSerializer.Serialize(processMessage, options);

            //var jSetting = new JsonSerializerSettings { NullValueHandling = NullValueHandling.Ignore };

            //string json2 = JsonConvert.SerializeObject(processMessage, jSetting);
            //string json3 = "{\"Id\":\"229165ae-13c9-4e60-bdeb-78295398635f\",\"Success\":true,\"Command\":\"hover\",\"MillisecondsTimeout\":2000,\"Position\":{\"X\":11,\"Y\":22},\"Highlight\":{\"Color\":\"#FF0000\",\"Duration\":2000},\"Attribute\":{\"Values\":{\"tag\":\"DIV\",\"id\":\"s-top-left\",\"class\":\"s-top-left-new s-isindex-wrap\"},\"Children\":[]}}";
            //ProcessMessage? result2 = JsonConvert.DeserializeObject<ProcessMessage>(json2);
            //ProcessMessage? result3 = JsonConvert.DeserializeObject<ProcessMessage>(json3);

            //ProcessMessage? result = System.Text.Json.JsonSerializer.Deserialize<ProcessMessage>(json);

            //int debug = 0;
            //debug++;

        }

        [Fact]
        public void Test4()
        {
            //NativeMessageClient nativeMessageClient = new NativeMessageClient();
            this.nativeMessageClient.Connect("NativeMessageHost2");
            //tasks[0] = nativeMessageClient.Connect();
            //tasks[0].Start();

            //Thread.Sleep(2000);

            Request request1 = new Request { Id= Guid.NewGuid().ToString(), Command = "hover" };
            request1.Position = new Position { X=11, Y=22 };
            request1.Highlight = new Highlight { Color="#FF0000", Duration=2000 };

            //this.nativeMessageClient.Write(processMessage);
            Response? result1 = this.nativeMessageClient.Send(request1);
            //ProcessMessage result1 = this.nativeMessageClient.Send("", processMessage);

            Request request2 = new Request { Id= Guid.NewGuid().ToString(), Command = "hover" };
            request2.Position = new Position { X=33, Y=44 };
            //request2.Highlight = new GRPCCommon.Highlight { Color="#FF0000", Duration=2000 };
            Response? result2 = this.nativeMessageClient.Send(request2);

            //this.nativeMessageClient.Close();
            int debug = 0;
            debug++;

        }

    }
}