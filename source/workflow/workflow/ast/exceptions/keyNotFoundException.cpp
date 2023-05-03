#include "keyNotFoundException.h"

namespace workflow::ast::exceptions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="object"></param>
    /// <param name="message"></param>
    KeyNotFoundException::KeyNotFoundException(void* object, std::string message) :Exception(object, message) { }
}