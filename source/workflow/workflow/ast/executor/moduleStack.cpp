#include "moduleStack.h"

using namespace std;
using namespace workflow::ast::executor;

void ModuleStack::push(map<string, Module*> value) {
    this->modules.push_back(value);
}

void ModuleStack::pop() {
    this->modules.pop_back();
}

/// <summary>
/// 获取最外层变量值
/// </summary>
Module* ModuleStack::getModule(string name) {
    return this->modules.back()[name];
}

/// <summary>
/// 设置最外层变量值
/// 值存在的时候更新值
/// 值不存在的时候创建值
/// </summary>
void ModuleStack::setModule(string name, Module* value) {
    this->modules.back()[name] = value;
}

/// <summary>
/// 当前模块的函数
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
FunctionDefinition* ModuleStack::getFunction(string name) {
    this->modules.back()[name];
}

void ModuleStack::setFunction(string name, FunctionDefinition* value) {

}

/// <summary>
/// 指定模块的函数
/// </summary>
/// <param name="mdouleName"></param>
/// <param name="functionName"></param>
/// <returns></returns>
FunctionDefinition* ModuleStack::getFunction(string mdouleName, string functionName) {
    // this->modules.back()[name]
}