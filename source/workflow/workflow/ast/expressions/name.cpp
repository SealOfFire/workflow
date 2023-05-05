#include "name.h"
#include "../exceptions/keyNotFoundException.h"
#include "../exceptions/nullReferenceException.h"
#include "../modules/module.h"

using namespace std;
using namespace workflow::ast::types;
using namespace workflow::ast::expressions;

namespace workflow::ast::expressions {
    Name::Name(string id) : id(id) {}

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    Object* Name::execute(Context* context) {

        if (context->currentModule == nullptr) {
            // 模块不存在
            throw ast::exceptions::NullReferenceException(this, EXPECTION_MESSAGE_NAME_MODULE);
        }

        if (context->currentModule->variables.count(this->id) == 0) {
            // 变量不存在
            throw ast::exceptions::KeyNotFoundException(this, EXPECTION_MESSAGE_NAME_ID + this->id);
        }

        return context->currentModule->variables[this->id];
        //return context->variables.getValue(this->id);
    }

    string Name::getClassName() const {
        return Name::className;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Name::toScriptCode(Context* context) {
        return this->id;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    std::string Name::isName() {
        return this->id;
    }

}