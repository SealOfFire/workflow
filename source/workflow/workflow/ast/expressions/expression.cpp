#include "expression.h"

using namespace std;
using namespace workflow::ast;
using namespace workflow::ast::executors;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    /// <summary>
    /// 执行脚本
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* Expression::run(Context* context) {
        if (context->executeMode == ExecuteMode::Debug) {
            // TODO 断点或单步
            // cout << "断点或单步" << this->getClassName() << endl;
            this->debugProcess(context);
        }

        return this->execute(context);
    }

    /// <summary>
    /// 每个脚本子类自己实现执行脚本时的功能
    /// </summary>
    /// <returns></returns>
    Object* Expression::execute(Context* context) {
        return nullptr;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Expression::getClassName() const {
        return Expression::className;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    void Expression::debugProcess(Context* context) {
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
    string Expression::toScriptCode(Context* context) {
        //ring indent(context->indentCount * context->indentLevel, ' ');
        return "ScriptCode";
    }

    /// <summary>
    /// 表达式是否是变量。如果是变量，返回变量名字符串
    /// 不是变量返回空字符串
    /// </summary>
    /// <returns></returns>
    std::string Expression::isName() {
        return std::string();
    }
}