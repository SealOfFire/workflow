#include "luaExpression.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::types;

namespace workflow::framework::expressions {

    /// <summary>
    /// 计算表达式
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* LuaExpression::execute(Context* context) {
        // TODO
        return nullptr;
    }

    std::string LuaExpression::toScriptCode(Context* context) {
        return "LuaExpression(" + this->value + ")";
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string LuaExpression::getClassName() const {
        return LuaExpression::className;
    }
}