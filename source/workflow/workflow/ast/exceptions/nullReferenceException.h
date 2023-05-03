#pragma once
#include "exception.h"

namespace workflow::ast::exceptions {

    /// <summary>
    /// 对象为空异常
    /// </summary>
    class SHARED_LIB_API NullReferenceException : public Exception {
    public:

        /// <summary>
        /// 
        /// </summary>
        /// <param name="object"></param>
        /// <param name="message"></param>
        NullReferenceException(void* object, std::string message);
    };
}