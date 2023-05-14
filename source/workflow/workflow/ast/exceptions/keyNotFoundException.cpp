#include "keyNotFoundException.h"

namespace workflow::ast::exceptions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="object"></param>
    /// <param name="message"></param>
    KeyNotFoundException::KeyNotFoundException(void* object, std::string name) :name(name), Exception(object, ERROR_MESSAGE_keyNotFoundException) { }

    std::string KeyNotFoundException::what() const {
        return Exception::what() + ":" + this->name;
    }
}