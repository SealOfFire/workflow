#include "assign.h"
#include "../expressions/name.h"
#include "../modules/module.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::expressions;
using namespace workflow::ast::types;

namespace workflow::ast::statements {

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="target"></param>
    /// <param name="value"></param>
    Assign::Assign(Expression* target, Expression* value) : target(target), value(value) {}

    /// <summary>
    /// 运行组件赋值过程
    /// </summary>
    void Assign::execute(Context* context) {
        // 赋值。常量赋值给变量， 变量赋值给变量，计算的结果赋值给变量
        // 这里要考虑合适new 新的存储空间，何时传递指针

        if (this->target->getClassName() == Name::className) {
            // target是变量名
            // 变量名
            string name = ((Name*)this->target)->id;

            // 在变量存储空间中修改变量名对应的值
            //context->variables.setValue(name, this->value->run(context));
            context->currentModule->variables[name] = this->value->run(context);
        }
        else {
            // 字典。或者数组下标赋值
        }

    }

    string Assign::getClassName() const {
        return Assign::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string Assign::toScriptCode(Context* context) {
        string indent(context->indentCount * context->indentLevel, ' ');
        return indent + this->target->toScriptCode(context) + " = " + this->value->toScriptCode(context) + context->newline;
    }
}