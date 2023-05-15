#include "ast.h"
#include "exceptions/errorMessage.h"
#include "exceptions/exception.h"

namespace workflow::ast {

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    types::Boolean* Manager::createBoolean(bool value) {
        types::Boolean* result = new types::Boolean(value);
        Manager::variables.push_back(result);
        return result;
    }
    /*
    types::Dictionary* Manager::createDictionary() {
        types::Dictionary* result = new types::Dictionary();
        Manager::variables.push_back(result);
        return result;
    }
    */
    /*
    types::Float* Manager::createFloat(float value) {
        types::Float* result = new types::Float(value);
        Manager::variables.push_back(result);
        return result;
    }
    */

    //types::Integer* Manager::createInteger(int value) {
    //    types::Integer* result = new types::Integer(value);
    //    Manager::variables.push_back(result);
    //    return result;
    //}

    //types::List* Manager::createList() {
    //    types::List* result = new types::List();
    //    Manager::variables.push_back(result);
    //    return result;
    //}

    types::Null* Manager::createNull() {
        types::Null* result = new types::Null();
        Manager::variables.push_back(result);
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    types::Object* Manager::createObject() {
        types::Object* result = new types::Object();
        Manager::variables.push_back(result);
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    types::String* Manager::createString(std::string value) {
        types::String* result = new types::String(value);
        Manager::variables.push_back(result);
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    types::Void* Manager::createVoid() {
        types::Void* result = new types::Void();
        Manager::variables.push_back(result);
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    void Manager::deleteObject(types::Object* value) {
        std::vector<types::Object*>::iterator iter = std::find(Manager::variables.begin(), Manager::variables.end(), value);
        if (iter == Manager::variables.end()) {
            // 没找到
        }
        else {
            // 找到
            types::Object* target = *iter;
            if (target->getReferenceCount() != 0) {
                // 不能删除
                throw exceptions::Exception(target, ERROR_MESSAGE_ReferenceCount);
            }
            Manager::variables.erase(iter);
            delete target;
        }
    }

    void Manager::pushVariable(types::Object* value) {
        Manager::variables.push_back(value);
    }
}
