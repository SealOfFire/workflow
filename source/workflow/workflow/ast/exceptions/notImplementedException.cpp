#include "notImplementedException.h"

namespace workflow::ast::exceptions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="object"></param>
    /// <param name="message"></param>
    NotImplementedException::NotImplementedException(void* object, std::string name) :name(name), Exception(object, ERROR_MESSAGE_NotImplementedException) { }

    std::string NotImplementedException::what() const {
        return Exception::what() + ":" + this->name;
    }
}