using System.Windows.Forms;

static class Program
{
    [STAThread]
    static void Main()
    {
        Console.WriteLine("Hello, World!");

        //Class1 class1 = new Class1();
        //class1.test2();
        //class1.FindElement();
        //GlobalMouseHandler

        Console.WriteLine("Hello, World!");

        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);
        //Application.AddMessageFilter(new MouseMessageFilter());
        // MouseMessageFilter.MouseMove += new MouseEventHandler(OnGlobalMouseMove);
        Application.Run();
        Console.WriteLine("END");
    }

    static void OnGlobalMouseMove(object sender, MouseEventArgs e)
    {
        Console.WriteLine(e.Location.ToString());
    }
}