#include "object.h"

using namespace std;
using namespace workflow::ast::types;

/// <summary>
/// 构造函数
/// </summary>
/// <param name="value"></param>
/// <param name="valueType"></param>
//Object::Object(void* value) :value(value) {}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
string Object::getClassName() const {
    return Object::className;
}

string Object::toString() {
    return Object::className;
}

//Object Object::operator+(Object& value) {
//    return Object();
//}
Object* Object::Add(Object* value) {
    return this;
}

Object Object::Add(Object& value) {
    return Object();
}