#include "value.h"

namespace workflow::ast::expressions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    Value::Value(types::Object* value) : value(value) {}

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    types::Object* Value::execute(Context* context) {
        return this->value;
    }

    string Value::getClassName() const {
        return Value::className;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Value::toScriptCode(Context* context) {
        //return this->value->toScriptCode(context);
        return "this->value->toScriptCode(context);";
    }
}