#include "while.h"
#include "../types/boolean.h"

using namespace std;
using namespace workflow::ast::executor;
using namespace workflow::ast::statements;
using namespace workflow::ast::types;

/// <summary>
///
/// </summary>
void While::execute(Context* context) {
    Boolean* result = (Boolean*)this->test->run(context);

    while (result->value) {
        this->body->run(context);
    }

    delete result;
}

string While::getClassName() const {
    return While::className;
}

/// <summary>
/// 转换成脚本
/// </summary>
/// <returns></returns>
string While::toScriptCode(Context* context) {
    return "ScriptCode\r\n";
}