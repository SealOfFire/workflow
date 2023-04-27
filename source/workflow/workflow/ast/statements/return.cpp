#include "return.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::types;

namespace workflow::ast::statements {
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="value"></param>
    Return::Return(Expression* value) :value(value) {
    }

    void Return::execute(Context* context) {

        // 计算返回值
        Object* value = this->value->run(context);
    }

    string Return::getClassName()const {
        return Return::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string Return::toScriptCode(Context* context) {
        string indent(context->indentCount * context->indentLevel, ' ');
        return indent + "RETURN " + this->value->toScriptCode(context) + context->newline;
    }
}