#include "functionDefinition.h"
#include "module.h"
#include "../statements/container.h"
#include "../statements/return.h"
#include "../types/void.h"

using namespace std;
using namespace workflow::ast::expressions;
using namespace workflow::ast::modules;
using namespace workflow::ast::statements;
using namespace workflow::ast::types;

FunctionDefinition::FunctionDefinition(string name) : name(name) {
}

FunctionDefinition::~FunctionDefinition() {
}

/// <summary>
/// 
/// </summary>
/// <param name="context"></param>
void FunctionDefinition::call(Context* context) {
    // 当前模块的变量列表
    //context->variables = this->variables;
    context->variables.push(this->variables);

    for (Statement* child : this->body) {
        if (child->getClassName() == Return::className) {
            // 遇到返回语句的时候
            if (((Return*)child)->value == nullptr) {
                // void 函数
                //return new Void();
            }
            else {
                // 返回值
                Object* returnValue = ((Return*)child)->value->run(context);
                this->returns = returnValue;
            }
            break;
        }
        else {
            child->run(context);
        }
    }

    context->variables.pop();

    // TODO 执行到这里的时候说明函数中缺少return
    // cout << "函数中缺少return" << endl;
}

/// <summary>
/// 执行语句
/// </summary>
void FunctionDefinition::execute(Context* context) {

    // 把变量对象指针添加到上下文中
    // TODO 添加到父类模块的函数列表中
    context->functions[this->name] = this;
    if (this->parent != nullptr) {
        if (this->parent->getClassName() == Module::className) {
            ((Module*)this->parent)->functions[this->name] = this;
        }
    }
}

string FunctionDefinition::getClassName() const {
    return FunctionDefinition::className;
}

void FunctionDefinition::addStatement(Statement* statement) {
    this->body.push_back(statement);
}

string FunctionDefinition::toScriptCode(Context* context) {
    string indent(context->indentCount * context->indentLevel, ' ');

    string output = indent + "FUNCTION " + this->name + context->newline;
    output += indent + "{" + context->newline;
    context->indentLevel++;

    for (Statement* child : this->body) {
        output += child->toScriptCode(context);
    }

    context->indentLevel--;
    output += indent + "}" + context->newline;


    return output;
}