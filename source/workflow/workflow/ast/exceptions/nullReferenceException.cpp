#include "nullReferenceException.h"

namespace workflow::ast::exceptions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="object"></param>
    /// <param name="message"></param>
    NullReferenceException::NullReferenceException(void* object, std::string message) :Exception(object, message) { }
}