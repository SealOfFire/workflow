#include "dictionary.h"
#include "../exceptions/keyNotFoundException.h"

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    Dictionary::Dictionary() {}

    Dictionary::~Dictionary() {
        std::map<std::string, types::Object*>::iterator iter;
        for (iter = this->value.begin(); iter != this->value.end();) {
            iter->second->decreaseReferenceCount();
            Object::release(iter->second);
            iter->second = nullptr;
            this->value.erase(iter++);
        }
        this->value.clear();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    Dictionary* Dictionary::create() {
        Dictionary* result = new Dictionary();
        result->autoRelease = false;
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    void Dictionary::set(String* key, Object* value) {
        this->set(key->value, value);
    }

    void Dictionary::set(std::string key, Object* value) {
        value->increaseReferenceCount();
        if (this->value.count(key) == 0) {
        }
        else {
            this->remove(key);
        }
        this->value[key] = value;
    }

    Object* Dictionary::get(String* key) {
        return this->get(key->value);
    }

    Object* Dictionary::get(std::string key) {
        if (this->value.count(key) == 0) {
            throw exceptions::KeyNotFoundException(this, key);
        }
        return this->value[key];
    }

    void Dictionary::remove(String* key) {
        this->remove(key->value);
    }

    void Dictionary::remove(std::string key) {
        if (this->value.count(key) == 0) {
            throw exceptions::KeyNotFoundException(this, key);
        }
        Object* value = this->value[key];
        this->value.erase(key);
        value->decreaseReferenceCount();
        //Object::release(value);
    }

    bool Dictionary::hasKey(String* key) {
        return this->hasKey(key->value);
    }

    bool Dictionary::hasKey(std::string key) {
        if (this->value.count(key) == 0) {
            return false;
        }
        else {
            return true;
        }
    }

    std::map<std::string, types::Object*>::iterator Dictionary::begin() {
        //std::map<std::string, types::Object*>::iterator iter = this->value.begin();
        return  this->value.begin();
    }

    std::map<std::string, types::Object*>::iterator Dictionary::end() {
        //std::map<std::string, types::Object*>::iterator iter = this->value.end();
        return this->value.end();
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