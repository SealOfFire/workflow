#include "boolean.h"

using namespace std;

namespace workflow::ast::types {
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="value"></param>
    Boolean::Boolean(bool value) : value(value) {}

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Boolean::getClassName() const {
        return Boolean::className;
    }

    string Boolean::toString() {
        if (this->value) {
            return "true";
        }
        else {
            return "false";
        }
    }
}