namespace UIAutomation.Exceptions
{
    /// <summary>
    /// 浏览器插件异常
    /// </summary>
    public class BrowserExtensionException : Exception
    {
        public BrowserExtensionException() : base("浏览器插件异常") { }

        public BrowserExtensionException(string message) : base(message) { }
    }
}
