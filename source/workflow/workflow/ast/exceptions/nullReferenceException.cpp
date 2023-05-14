#include "nullReferenceException.h"

namespace workflow::ast::exceptions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="object"></param>
    /// <param name="message"></param>
    NullReferenceException::NullReferenceException(void* object, std::string name) :name(name), Exception(object, ERROR_MESSAGE_NullPointerException) { }

    std::string NullReferenceException::what() const {
        return Exception::what() + ":" + this->name;
    }
}