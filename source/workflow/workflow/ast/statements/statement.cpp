#include "statement.h"

using namespace std;
using namespace workflow::ast::executors;
using namespace workflow::ast::statements;

namespace workflow::ast::statements {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    void Statement::run(Context* context) {
        if (context->executeMode == ExecuteMode::Debug) {
            // TODO 断点或单步
            this->debugProcess(context);
            // cout << "断点或单步" << this->getClassName() << endl;
        }

        this->execute(context);
    }

    /// <summary>
    ///
    /// </summary>
    void Statement::execute(Context* context) {
        // cout << "断点或单步" << this->getClassName() << endl;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Statement::getClassName() const {
        return Statement::className;
    }

    /// <summary>
    /// debug模式运行时的处理
    /// </summary>
    void Statement::debugProcess(Context* context) {
        // 当前语句是断点，或者单步执行
        // TODO 判断是断点
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
    string Statement::toScriptCode(Context* context) {
        string indent(context->indentCount * context->indentLevel, ' ');
        return indent + "ScriptCode" + context->newline;
    }

}