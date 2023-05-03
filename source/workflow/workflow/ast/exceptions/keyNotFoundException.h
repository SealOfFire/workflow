#pragma once
#include "exception.h"

namespace workflow::ast::exceptions {

    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API KeyNotFoundException : public Exception {
    public:

        /// <summary>
        /// 
        /// </summary>
        /// <param name="object"></param>
        /// <param name="message"></param>
        KeyNotFoundException(void* object, std::string message);
    };
}