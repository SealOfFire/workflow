#pragma once
#include <string>
#include <vector>
#include <map>
#include "../modules/module.h"
#include "../modules/functionDefinition.h"

using namespace std;
using namespace workflow::ast::modules;

namespace workflow::ast::executor {

    /// <summary>
    /// 模块栈
    /// </summary>
    class ModuleStack {
    public:
        vector<map<string, Module*>> modules;

        void push(map<string, Module*> value);

        void pop();

        /// <summary>
        /// 获取最外层变量值
        /// </summary>
        Module* getModule(string name);

        /// <summary>
        /// 设置最外层变量值
        /// 值存在的时候更新值
        /// 值不存在的时候创建值
        /// </summary>
        void setModule(string name, Module* value);

        /// <summary>
        /// 当前模块的函数
        /// </summary>
        /// <param name="functionName"></param>
        /// <returns></returns>
        FunctionDefinition* getFunction(string functionName);

        void setFunction(string functionName, FunctionDefinition* value);

        /// <summary>
        /// 指定模块的函数
        /// </summary>
        /// <param name="mdouleName"></param>
        /// <param name="functionName"></param>
        /// <returns></returns>
        FunctionDefinition* getFunction(string mdouleName, string functionName);

        void setFunction(string mdouleName, string functionName, FunctionDefinition* value);
    }
}