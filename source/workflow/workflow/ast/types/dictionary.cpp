#include "dictionary.h"

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    Dictionary::Dictionary() {}

    string Dictionary::getClassName() const {
        return Dictionary::className;
    }

    string Dictionary::toString() {
        std::string output = "{";
        for (auto [key, val] : this->value) {
            output += key + ":" + val->toString() + ", ";
        }
        output += "}";
        return output;
    }
}