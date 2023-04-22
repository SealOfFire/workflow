#include "compare.h"

using namespace std;
using namespace workflow::ast::types;
using namespace workflow::ast::expressions;


Object* Compare::execute(Context* context) {
    //return context->variables[this->id];
    return nullptr;
}

string Compare::getClassName() const {
    return  Compare::className;
}

/// <summary>
/// 转换成脚本
/// </summary>
/// <returns></returns>
string Compare::toScriptCode(Context* context) {
    //ring indent(context->indentCount * context->indentLevel, ' ');
    return "ScriptCode";
}