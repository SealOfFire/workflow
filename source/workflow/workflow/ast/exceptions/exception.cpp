#include "exception.h"

using namespace std;
using namespace workflow::ast::exceptions;

Exception::Exception(string message) :message(message) {}

string Exception::what() const {
    return this->message;
}