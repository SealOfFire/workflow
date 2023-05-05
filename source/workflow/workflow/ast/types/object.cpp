#include "object.h"

using namespace std;

namespace workflow::ast::types {
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

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    int Object::getReferenceCount() {
        return this->referenceCount;
    }

    /// <summary>
    /// 
    /// </summary>
    void Object::increaseReferenceCount() {
        this->referenceCount += 1;
    }

    /// <summary>
    /// 
    /// </summary>
    void Object::decreaseReferenceCount() {
        if (this->referenceCount == 0) {
            // TODO 减少报错
        }
        this->referenceCount -= 1;
    }

    /// <summary>
    /// 释放object类型对象
    /// </summary>
    /// <param name="object"></param>
    void Object::release(Object* object) {
        if (object->getReferenceCount() <= 0) {
            delete object;
        }
    }
}