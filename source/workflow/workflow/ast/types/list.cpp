#include "list.h"
#include "../exceptions/exception.h"

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    List::List() {}

    List::~List() {
        for (int i = 0; i < this->value.size(); i++) {
            this->value[i]->decreaseReferenceCount();
            Object::release(this->value[i]);
        }
        this->value.clear();
    }

    List* List::create() {
        List* result = new List();
        result->autoRelease = false;
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="item"></param>
    void List::append(Object* item) {
        item->increaseReferenceCount();
        this->value.push_back(item);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    size_t List::count() {
        return this->value.size();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    Object* List::elementAt(size_t index) {
        return this->value[index];
    }

    void List::insert(size_t index, Object* item) {
        // 原本索引处如果有数据，删除原有的数据
        if (this->value.size() > index) {
            Object* oldValue = this->value[index];
            oldValue->decreaseReferenceCount();
            Object::release(oldValue);
        }
        item->increaseReferenceCount();
        this->value[index] = item;
    }

    void List::remove(Object* item) {
        std::vector<types::Object*>::iterator iter = std::find(this->value.begin(), this->value.end(), item);
        if (iter == this->value.end()) {
            // 没找到
            throw exceptions::Exception(this, item->toString() + "不在list中");
        }
        else {
            // 找到
            this->value.erase(iter);
            item->decreaseReferenceCount();
            Object::release(item);
        }
    }

    void List::removeAt(size_t index) {
        if (this->value.size() > index) {
            Object* oldValue = this->value[index];
            this->value.erase(this->value.begin() + index);
            oldValue->decreaseReferenceCount();
            Object::release(oldValue);
        }
        else {
            throw exceptions::Exception(this, "索引超出范围");
        }
    }

    /// <summary>
   /// 
   /// </summary>
   /// <returns></returns>
    string List::getClassName() const {
        return List::className;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string List::toString() {
        // return std::to_string(this->value);
        std::string output = "[";
        for (int i = 0; i < this->value.size(); i++) {
            output += this->value[i]->toString() + ", ";
        }
        output += "]";
        return output;
    }

}
