#include "call.h"
#include "../modules/functionDefinition.h"
#include "../modules/module.h"

using namespace std;
using namespace workflow::ast::modules;
using namespace workflow::ast::types;
using namespace workflow::ast::expressions;

/// <summary>
/// 构造函数
/// </summary>
/// <param name="name">函数名</param>
Call::Call(string name, map<string, Expression*> arguments) :name(name), arguments(arguments) {
}

Object* Call::execute(Context* context) {
    //return context->variables[this->id];

    // 循环入参的表达式列表，计算入参

    // 设置输入变量值
    // TODO 如何获取这个函数变量
    //FunctionDefinition* func = new FunctionDefinition(this->name);
    FunctionDefinition* func = context->functions[this->name];

    // 计算输入参数列表
    for (auto [name, expr] : this->arguments) {
        // 计算结果直接放入函数的局域变量列表
        func->variables[name] = expr->run(context);
    }

    // 执行函数
    func->call(context);

    // 函数的返回值
    if (func->returns == nullptr) {
        // void 函数
    }
    else {
        return func->returns;
    }

    return nullptr;
}

string Call::getClassName() const {
    return Call::className;
}

/// <summary>
/// 转换成脚本
/// </summary>
/// <returns></returns>
string Call::toScriptCode(Context* context) {

    string args;
    // 计算输入参数列表
    for (auto [name, expr] : this->arguments) {
        args += expr->toScriptCode(context) + ", ";
    }

    return "CALL " + this->name + "(" + args + ")";
}