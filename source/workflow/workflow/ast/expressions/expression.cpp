#include "expression.h"

using namespace std;
using namespace workflow::ast::expressions;

Object* Expression::run(Context* context) {
    if (context->executeMode == ExecuteMode::Debug) {
        // TODO 断点或单步
        // cout << "断点或单步" << this->getClassName() << endl;
        this->debugProcess(context);
    }

    return this->execute(context);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
Object* Expression::execute(Context* context) {
    return nullptr;
}

string Expression::getClassName() const {
    return Expression::className;
}

void Expression::debugProcess(Context* context) {
    // 当前语句是断点，或者单步执行
    if (this->breakpoint || context->debugMode == DebugMode::NextStatement) {
        // 暂停线程
        cout << "断点或单步:" << this->getClassName() << endl;

        unique_lock<mutex> locker(context->mutex);
        context->conditionVariable.wait(locker);
    }
}

/// <summary>
/// 转换成脚本
/// </summary>
/// <returns></returns>
string Expression::toScriptCode(Context* context) {
    //ring indent(context->indentCount * context->indentLevel, ' ');
    return "ScriptCode";
}