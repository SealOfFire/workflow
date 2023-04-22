#include "print.h"

using namespace std;
using namespace workflow::ast::executor;
using namespace workflow::ast::types;

/// <summary>
/// 
/// </summary>
/// <param name="value"></param>
Print::Print(Expression* value) :value(value) {
}

void Print::execute(Context* context) {

    // 计算返回值
    Object* value = this->value->run(context);
    cout << value->toString() << endl;
}

string Print::getClassName()const {
    return Print::className;
}

/// <summary>
/// 转换成脚本
/// </summary>
/// <returns></returns>
string Print::toScriptCode(Context* context) {
    string indent(context->indentCount * context->indentLevel, ' ');
    return indent + "PRINT(" + this->value->toScriptCode(context) + ")" + context->newline;
}