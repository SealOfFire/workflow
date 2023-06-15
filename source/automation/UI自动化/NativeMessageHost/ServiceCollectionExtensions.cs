using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.DependencyInjection.Extensions;
using NativeMessageHost.Handles;
using System.Reflection;

namespace NativeMessageHost
{
    public static class ServiceCollectionExtensions
    {
        /// <summary>
        /// 通过反射自动注入处理类
        /// </summary>
        /// <param name="services"></param>
        /// <returns></returns>
        public static IServiceCollection AddHandles(this IServiceCollection services)
        {
            // 通过反射自动注入处理类
            Assembly? assembly = Assembly.GetAssembly(typeof(BaseHandle));
            if (assembly !=null)
            {
                foreach (Type type in assembly.GetTypes())
                {
                    // 类的判断
                    if (type.BaseType == typeof(BaseHandle))
                    {
                        services.AddSingleton(typeof(BaseHandle), type);
                    }
                    // 接口的判断
                    //Type? t = type.GetInterface(typeof(BaseHandle).Name);
                    //if (t != null)
                    //{
                    //    services.TryAddSingleton(type);
                    //}
                }
            }

            return services;
        }
    }
}
