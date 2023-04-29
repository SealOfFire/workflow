﻿#include "name.h"
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