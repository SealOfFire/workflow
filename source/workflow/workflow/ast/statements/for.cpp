#include "for.h"
#include "../expressions/name.h"
#include "../modules/module.h"
#include "../types/list.h"

namespace workflow::ast::statements {

    For::For(expressions::Expression* target, expressions::Expression* iteration, Statement* body) :target(target), iteration(iteration), body(body) {}

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    void For::execute(Context* context) {

        Object* iterationResult = this->iteration->run(context);

        std::string name = this->target->isName();
        if (name.size() == 0) {
            // TODO 迭代的数据不是变量
        }

        if (iterationResult->getClassName() == types::List::className) {
            types::List* list = (types::List*)iterationResult;

            for (int i = 0; i < list->value.size(); i++) {
                // 
                context->currentModule->variables[name] = list->value[i];
                this->body->run(context);
            }

            // 删除局部变量
            if (list->value.size() > 0) {
                context->currentModule->variables.erase(name);
            }
        }
        else {
            // TODO 不可迭代数据
        }

    }

    std::string For::getClassName() const {
        return For::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    std::string For::toScriptCode(Context* context) {
        string indent(context->indentCount * context->indentLevel, ' ');
        std::string output = indent + "FOR " + this->target->toScriptCode(context) + " IN " + this->iteration->toScriptCode(context) + context->newline;
        output += indent + "{" + context->newline;
        context->indentLevel++;
        output += this->body->toScriptCode(context);
        context->indentLevel--;
        output += indent + "}" + context->newline;

        return output;
    }
}