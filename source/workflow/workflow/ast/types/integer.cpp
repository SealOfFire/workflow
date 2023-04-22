#include "integer.h"

using namespace std;
using namespace workflow::ast::types;

/// <summary>
/// 构造函数
/// </summary>
/// <param name="value"></param>
Integer::Integer(int value) : value(value) {}


string Integer::getClassName() const {
    return Integer::className;
}

string Integer::toString() {
    return std::to_string(this->value);
}