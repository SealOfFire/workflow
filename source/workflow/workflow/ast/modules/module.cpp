#include "module.h"
#include "../statements/container.h"

using namespace workflow::ast::executor;
using namespace workflow::ast::modules;
using namespace workflow::ast::statements;
using namespace workflow::ast::types;

Module::Module(string name) :name(name) {
}

Module::~Module() {
    //
    if (this->body != nullptr) {
        //delete this->body;
    }
}

/// <summary>
/// 执行语句
/// </summary>
void Module::execute(Context* context) {

    // 当前模块的变量列表
    context->variables.push(this->variables);
    //context->parent = this;
    context->modules[this->name] = this;

    //
    this->body->run(context);

    // 只保留当前层内的模块，方便函数调用
    // 不能移除
    //context->modules.erase(this->name);
    //context->parent = nullptr;
    context->variables.pop();
}

string Module::getClassName() const {
    return Module::className;
}

void Module::addStatement(Statement* statement) {

    statement->parent = this;

    if (this->body == nullptr) {
        // 当前body是空，直接添加
        this->body = statement;
    }
    else if (this->body->getClassName() == Container::className) {
        // 当前是容器组件，直接添加
        ((Container*)this->body)->children.push_back(statement);
    }
    else {
        // 创建一个容器组件
        Container* container = new Container();
        container->children.push_back(this->body); // 原本的body语句
        container->children.push_back(statement); // 新加的语句
        this->body = container;
    }
}

/// <summary>
/// 向模块中添加函数
/// </summary>
/// <param name="name"></param>
/// <param name="function"></param>
//void Module::addFunction(string name, Function* function) {}

/// <summary>
/// 转换成脚本
/// </summary>
/// <returns></returns>
string Module::toScriptCode(Context* context) {
    string indent(context->indentCount * context->indentLevel, ' ');

    string output = indent + "MODULE " + this->name + context->newline;
    output += indent + "{" + context->newline;
    context->indentLevel++;

    if (this->body != nullptr) {
        output += this->body->toScriptCode(context);
    }

    context->indentLevel--;
    output += indent + "}" + context->newline;


    return output;
}