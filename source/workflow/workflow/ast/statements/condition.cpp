﻿#include "condition.h"
#include "../types/boolean.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::statements;
using namespace workflow::ast::types;

/// <summary>
/// 执行语句
/// </summary>
void Condition::execute(Context* context) {
    Boolean* result = (Boolean*)this->test->run(context);

    /*
    Object *result = this->test->run(env);
    if (result->getClassName() != "workflow::ast::Boolean") {
        // TODO 不是bool类型
    }
    */

    if (result->value) {
        this->body->run(context);
    }
    else {
        this->orelse->run(context);
    }

    // result是计算获取的新值。这里需要删除，如果是从局域变量里获取的值。这里不删除
    Object::release(result);
}

string Condition::getClassName() const {
    return Condition::className;
}

/// <summary>
/// 转换成脚本
/// </summary>
/// <returns></returns>
string Condition::toScriptCode(Context* context) {
    string indent(context->indentCount * context->indentLevel, ' ');

    string output = indent + "IF(" + this->test->toScriptCode(context) + ")" + context->newline;
    context->indentLevel++;
    output += indent + "{" + context->newline;
    output += this->body->toScriptCode(context);
    output += indent + "}" + context->newline;
    output += indent + "ELSE" + context->newline;
    output += indent + "{" + context->newline;
    output += this->orelse->toScriptCode(context);
    output += indent + "}" + context->newline;
    context->indentLevel--;

    return output;
}