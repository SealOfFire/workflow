#include "float.h"

using namespace std;

namespace workflow::ast::types {

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="value"></param>
    Float::Float(float value) : value(value) {}

    Float* Float::create(float value) {
        Float* result = new Float(value);
        result->autoRelease = false;
        return result;
    }

    string Float::getClassName() const {
        return Float::className;
    }

    string Float::toString() {
        return std::to_string(this->value);
    }

}