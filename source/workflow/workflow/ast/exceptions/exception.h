#pragma once
#include <string>

using namespace std;

namespace workflow::ast::exceptions {

    /// <summary>
    /// 表达式异常
    /// </summary>
    class Exception
    {
    public:
        string message;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="message"></param>
        Exception(string message);

        virtual string what() const;

    };
}
