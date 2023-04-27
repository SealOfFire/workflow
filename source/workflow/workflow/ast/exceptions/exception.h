#pragma once
#include <string>
#include "../../exportLib.h"

using namespace std;

namespace workflow::ast::exceptions {

    /// <summary>
    /// 表达式异常
    /// </summary>
    class SHARED_LIB_API Exception
    {
    private:

        /// <summary>
        /// 错误消息
        /// </summary>
        string message;


    public:
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="message"></param>
        Exception(string message);

        virtual string what() const;

    };
}
