#include "variables.h"
#include "exceptions/exception.h"

namespace workflow::ast {

    Variables::Variables() {}

    Variables::~Variables() {
        std::map<std::string, types::Object*>::iterator iter;
        for (iter = this->value.begin(); iter != this->value.end();) {
            iter->second->decreaseReferenceCount();
            types::Object::release(iter->second);
            iter->second = nullptr;
            this->value.erase(iter++);
        }
        this->value.clear();
    }

    bool Variables::has(std::string name) {
        if (this->value.count(name) == 0) {
            return false;
        }
        else {
            return true;
        }
    }

    types::Object* Variables::get(std::string name) {
        if (this->has(name)) {
            return this->value[name];
        }
        else {
            throw exceptions::Exception(this, name + "局部变量不存在");
        }
    }

    void Variables::set(std::string name, types::Object* value) {
        if (this->has(name)) {
            types::Object* oldValue = this->value[name];
            oldValue->decreaseReferenceCount();
            types::Object::release(oldValue);
        }
        value->increaseReferenceCount();
        this->value[name] = value;
    }

    void Variables::remove(std::string name) {
        if (this->has(name)) {
            types::Object* oldValue = this->value[name];
            oldValue->decreaseReferenceCount();
            types::Object::release(oldValue);
            this->value.erase(name);
        }
        else {
            throw exceptions::Exception(this, name + "局部变量不存在");
        }
    }

    std::map<std::string, types::Object*>::iterator Variables::begin() {
        return  this->value.begin();
    }

    std::map<std::string, types::Object*>::iterator Variables::end() {
        return this->value.end();
    }
}