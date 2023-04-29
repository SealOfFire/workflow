#include "string.h"

using namespace std;

namespace workflow::ast::types {

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="value"></param>
    String::String(string value) : value(value) {}


    string String::getClassName() const {
        //return "workflow::ast::String";
        return String::className;
    }

    string String::toString() {
        return this->value;
    }

    string String::stringToUTF8(const std::string str) {
        //int nwLen = ::MultiByteToWideChar();
        return nullptr;
    }

    string String::UTF8ToString(const std::string str) {
        return nullptr;
    }
}