﻿#include "integer.h"

using namespace std;

namespace workflow::ast::types {
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="value"></param>
    Integer::Integer(int value) : value(value) {}

    Integer* Integer::create(int value) {
        Integer* result = new Integer(value);
        result->autoRelease = false;
        return result;
    }

    string Integer::getClassName() const {
        return Integer::className;
    }

    string Integer::toString() {
        return std::to_string(this->value);
    }

    Object* Integer::Add(Object* value) {
        int result = 0;
        if (value->getClassName() == Integer::className) {
            result = this->value + ((Integer*)value)->value;
        }
        return new Integer(result);
    }

    Object Integer::Add(Object& value) {
        //int result = this->value + value.value;
        return Integer(1);
    }
}