#include "float.h"

using namespace std;
using namespace workflow::ast::types;

/// <summary>
/// 构造函数
/// </summary>
/// <param name="value"></param>
Float::Float(float value) : value(value) {}


string Float::getClassName() const {
    return Float::className;
}

string Float::toString() {
    return std::to_string(this->value);
}