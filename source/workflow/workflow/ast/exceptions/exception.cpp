#include "exception.h"

using namespace std;

namespace workflow::ast::exceptions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="message"></param>
    Exception::Exception(string message) :message(message) {}

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Exception::what() const {
        return this->message;
    }

}