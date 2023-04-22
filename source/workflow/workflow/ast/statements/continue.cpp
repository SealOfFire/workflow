#include "continue.h"

using namespace std;
using namespace workflow::ast::statements;

string Continue::getClassName()const {
    return Continue::className;
}

/// <summary>
/// 转换成脚本
/// </summary>
/// <returns></returns>
string Continue::toScriptCode(Context* context) {
    string indent(context->indentCount * context->indentLevel, ' ');
    return indent + "CONTINUE" + context->newline;
}