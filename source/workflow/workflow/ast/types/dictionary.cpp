#include "dictionary.h"

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    Dictionary::Dictionary() {}

    Dictionary::~Dictionary() {
        // TODO 删除map
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    void Dictionary::add(String* key, Object* value) {
        // TODO
    }

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