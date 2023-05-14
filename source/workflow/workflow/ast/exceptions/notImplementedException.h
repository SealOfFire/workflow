#pragma once
#include "exception.h"

namespace workflow::ast::exceptions {

    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API NotImplementedException : public Exception {
    public:
        /// <summary>
        /// 
        /// </summary>
        /// <param name="object"></param>
        /// <param name="message"></param>
        NotImplementedException(void* object, std::string name);

        virtual string what() const;

    protected:
        std::string name;
    };
}