﻿#include "dictionary.h"

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    Dictionary::Dictionary() {}

    string Dictionary::getClassName() const {
        return Dictionary::className;
    }

    string Dictionary::toString() {
        return "{LIST}";
    }
}