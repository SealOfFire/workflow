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
}