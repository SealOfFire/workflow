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
}
