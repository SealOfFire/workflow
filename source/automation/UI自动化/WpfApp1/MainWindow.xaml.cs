using Gma.System.MouseKeyHook;
using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using GRPCCommon.Protobuf.Common;
using Newtonsoft.Json;
using System;
using System.Diagnostics;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Net.Http.Json;
using System.Threading.Tasks;
using System.Timers;
using System.Windows;
using UIAutomationServer;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        //private GrpcClientForWPF.Client client;
        private Grpc.Core.Channel channel;
        private SelectorService.SelectorServiceClient selectorClient;
        private System.Timers.Timer mouseSamplingTimer;
        private bool isMouseSampling = false;

        private bool ctrlIsPress = false;
        private int x, y;

        private IKeyboardMouseEvents m_GlobalHook;

        private UIAutomationServer.UIAType uidtype = UIAType.Uia2;
        private int uiaTypa = 0;

        // http client
        private static HttpClient httpClient = new HttpClient();

        public MainWindow()
        {
            Trace.WriteLine($"MainWindow");

            InitializeComponent();
            this.mouseSamplingTimer = new System.Timers.Timer();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            this.channel = new Channel("localhost:5259", ChannelCredentials.Insecure);
            this.selectorClient = new SelectorService.SelectorServiceClient(this.channel);

            httpClient.BaseAddress = new System.Uri("http://localhost:5045/");
            httpClient.DefaultRequestHeaders.Accept.Clear();
            httpClient.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));

            this.mouseSamplingTimer.Elapsed +=this.mouseSamplingTimer_Elapsed;


            //System.Timers.Timer timer = new System.Timers.Timer();
            //timer.Elapsed += delegate
            //{
            //    this.Dispatcher.Invoke(new Action(delegate
            //    {
            //        Mouse.Capture(this);
            //        Point position = Mouse.GetPosition(this);
            //        Point positionOnScreen = PointToScreen(position);
            //        this.lable.Content = positionOnScreen;

            //        UIAutomationServer.SelectorReponse reponse = this.selectorClient.HoverElement(new HoverRequest
            //        {
            //            X= (int)positionOnScreen.X,
            //            Y =(int)positionOnScreen.Y,
            //            Color = "#FF0000",
            //            Duration=2,
            //            Type= UIAutomationServer.UIAType.Uia2
            //        });
            //        Mouse.Capture(null);
            //    }));
            //};
            //timer.Interval = 2000;
            //timer.Start();

            //this.Subscribe();

        }

        #region 调用web api

        private async Task Hover(int x, int y, string color, int duration, int automationType)
        {
            var request = new
            {
                id = Guid.NewGuid(),
                command = "hover",
                automationType = automationType,
                millisecondsTimeout = 2000,
                position = new
                {
                    x = x,
                    y = y,
                },
                highlight = new
                {
                    color = color,
                    duration = duration,
                }
            };
            HttpResponseMessage response = await httpClient.PostAsJsonAsync("UIAutomation/Hover", request);
            //response.EnsureSuccessStatusCode();
            if (response.IsSuccessStatusCode)
            {
                //product = await response.Content.ReadAsAsync<Product>();
            }
        }

        private async Task PickUp(int x, int y, int automationType)
        {
            GRPCCommon.Protobuf.UIAutomation.PickUpRequest request = new GRPCCommon.Protobuf.UIAutomation.PickUpRequest
            {
                Position = new Position { X=x, Y=y }
            };
            HttpResponseMessage response = await httpClient.PostAsJsonAsync("UIAutomation/PickUp", request);
            if (response.IsSuccessStatusCode)
            {
                //product = await response.Content.ReadAsAsync<Product>();
            }
        }

        private async Task Highlight(GRPCCommon.Protobuf.Common.Attribute attribute)
        {
            GRPCCommon.Protobuf.UIAutomation.HighlightRequest request = new GRPCCommon.Protobuf.UIAutomation.HighlightRequest
            {
                Attribute = attribute,
            };
            HttpResponseMessage response = await httpClient.PostAsJsonAsync("UIAutomation/Highlight", request);
            if (response.IsSuccessStatusCode)
            {
                //product = await response.Content.ReadAsAsync<Product>();
            }
        }

        #endregion

        /// <summary>
        /// 拾取
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pickup_Click(object sender, RoutedEventArgs e)
        {
            this.StartMouseSampling();
        }

        /// <summary>
        /// 高亮
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void highlight_Click(object sender, RoutedEventArgs e)
        {
            if (!string.IsNullOrEmpty(this.selector.Text))
            {
                Element? element = JsonConvert.DeserializeObject<Element>(this.selector.Text);
                if (element != null)
                {
                    await this.Highlight(new GRPCCommon.Protobuf.Common.Attribute());

                    //SelectorRequest request = new SelectorRequest();
                    //request.Selector = element;
                    //request.Type =this.uidtype;
                    //request.Color= "#FFFF00";
                    //request.Duration=2000;
                    //this.selectorClient.Highlight(request);
                }
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private async void mouseSamplingTimer_Elapsed(object? sender, ElapsedEventArgs e)
        {
            //await this.HoverElement(this.x, this.y, "#FF0000", 2000, this.uiaTypa);
            await this.Hover(this.x, this.y, "#FF0000", 2000, this.uiaTypa);

            //UIAutomationServer.SelectorReponse reponse = this.selectorClient.HoverElement(new HoverRequest
            //{
            //    X=this.x,
            //    Y =this.y,
            //    Color = "#FF0000",
            //    Duration=2000,
            //    Type= this.uidtype
            //});

            //this.Dispatcher.Invoke(new Action(delegate
            //{
            //    Mouse.Capture(this);
            //    Point position = Mouse.GetPosition(this);
            //    Point positionOnScreen = PointToScreen(position);
            //    this.lable.Content = positionOnScreen;

            //    UIAutomationServer.SelectorReponse reponse = this.selectorClient.HoverElement(new HoverRequest
            //    {
            //        X= (int)positionOnScreen.X,
            //        Y =(int)positionOnScreen.Y,
            //        Color = "#FF0000",
            //        Duration=2,
            //        Type= UIAutomationServer.UIAType.Uia2
            //    });

            //    Mouse.Capture(null);

            //    //bool isCtrl = Keyboard.Modifiers.HasFlag(ModifierKeys.Control);
            //    //if (isCtrl)
            //    //{
            //    //    string output = JsonConvert.SerializeObject(reponse.Element);
            //    //    this.selector.Text = output;
            //    //}
            //}));
        }

        private void Window_MouseEnter(object sender, System.Windows.Input.MouseEventArgs e)
        {
            //this.Background = 
            //this.lable.Content = "enter";
            // 暂停选取
            this.PauseMouseSampling();
        }

        private void Window_MouseLeave(object sender, System.Windows.Input.MouseEventArgs e)
        {
            //this.lable.Content = "leave";
            // 恢复选取
            this.ResumeMouseSampling();
        }

        /// <summary>
        /// 开始鼠标采样
        /// </summary>
        private void StartMouseSampling()
        {
            //bool result = Mouse.Capture(this);
            //if (!result)
            //{
            //    throw new Exception("没有获取到鼠标");
            //}
            // 采样间隔时间
            this.mouseSamplingTimer.Interval = 2000;
            this.isMouseSampling=true;
            //this.mouseSamplingTimer.Start();

            this.Subscribe();
        }

        private void StopMouseSampling()
        {
            this.isMouseSampling=false;
            this.mouseSamplingTimer.Stop();
            // Mouse.Capture(null); // 释放鼠标

            this.Unsubscribe();
        }

        private void PauseMouseSampling()
        {
            if (this.isMouseSampling)
            {
                this.mouseSamplingTimer.Stop();
            }
        }

        private void ResumeMouseSampling()
        {
            if (this.isMouseSampling)
            {
                this.mouseSamplingTimer.Start();
            }
        }

        public void Subscribe()
        {
            // Note: for the application hook, use the Hook.AppEvents() instead
            m_GlobalHook = Hook.GlobalEvents();

            m_GlobalHook.MouseDownExt += GlobalHookMouseDownExt;
            m_GlobalHook.KeyPress += GlobalHookKeyPress;
            m_GlobalHook.KeyDown+= GlobalHook_KeyDown;
            m_GlobalHook.KeyUp +=  GlobalHook_KeyUp;
            m_GlobalHook.MouseMove += GlobalHookMouseMove;
        }

        private void GlobalHook_KeyDown(object? sender, System.Windows.Forms.KeyEventArgs e)
        {
            Trace.WriteLine($"KeyPress: \t{e.KeyValue}");
            if (e.KeyValue == 162)
            {
                this.ctrlIsPress = true;
            }
        }

        private void GlobalHook_KeyUp(object? sender, System.Windows.Forms.KeyEventArgs e)
        {
            Trace.WriteLine($"KeyPress: \t{e.KeyValue}");
            if (e.KeyValue == 162)
            {
                this.ctrlIsPress = false;
            }
        }

        private void GlobalHookKeyPress(object? sender, System.Windows.Forms.KeyPressEventArgs e)
        {
            //Console.WriteLine("KeyPress: \t{0}", e.KeyChar);
            Trace.WriteLine($"KeyPress: \t{e.KeyChar}");
            if (e.KeyChar == (char)27)
            {
                this.StopMouseSampling();
            }
        }

        private async void GlobalHookMouseDownExt(object? sender, MouseEventExtArgs e)
        {
            Trace.WriteLine($"MouseDown: \t {e.Button}; \t System Timestamp: \t{e.Timestamp}");
            if (e.Button == System.Windows.Forms.MouseButtons.Left && this.ctrlIsPress)
            {
                this.StopMouseSampling();
                // 安装ctrl+鼠标左键拾取
                //await this.PickUpElement(this.x, this.y, this.uiaTypa);
                await this.PickUp(this.x, this.y, this.uiaTypa);

                //UIAutomationServer.SelectorReponse reponse = this.selectorClient.PickUpElement(new HoverRequest
                //{
                //    X=this.x,
                //    Y =this.y,
                //    Color = "#FF0000",
                //    Duration=2,
                //    Type= this.uidtype
                //});
                // 对象转成json
                //this.selector.Text = JsonConvert.SerializeObject(reponse.Selector);
            }
        }

        private void GlobalHookMouseMove(object? sender, System.Windows.Forms.MouseEventArgs e)
        {
            Trace.WriteLine($"mouse position:{e.Location}");
            this.x=e.Location.X;
            this.y=e.Location.Y;
        }

        public void Unsubscribe()
        {
            m_GlobalHook.MouseDownExt -= GlobalHookMouseDownExt;
            m_GlobalHook.KeyPress -= GlobalHookKeyPress;

            //It is recommened to dispose it
            m_GlobalHook.Dispose();
        }
    }
}

//https://www.codeproject.com/questions/900293/how-to-capture-mouse-down-event-outside-window