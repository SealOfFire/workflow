#pragma once
#include <string>
#include "errorMessage.h"
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

        /// <summary>
        /// 错误对象
        /// </summary>
        void* object;

    public:
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="message"></param>
        Exception(void* object, string message);

        virtual string what() const;

    };
}
