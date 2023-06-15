using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public App()
        {
            
        }

        protected override void OnStartup(StartupEventArgs e)
        {
            //Application.AddMessageFilter(new MouseMessageFilter());

            //EventManager.RegisterClassHandler(typeof(Window), Window.PreviewMouseDownEvent, new MouseButtonEventHandler(OnPreviewMouseDown));

            base.OnStartup(e);
        }

        //static void OnPreviewMouseDown(object sender, MouseButtonEventArgs e)
        //{
        //    Trace.WriteLine("Clicked!!");
        //}
    }
}
