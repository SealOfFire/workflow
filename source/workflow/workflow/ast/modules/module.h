#pragma once
#include <iostream>
#include <string>
#include <map>

#include "modules.h"
#include "functionDefinition.h"
#include "../statements/statement.h"
#include "../types/object.h"
#include "../../exportLib.h"

using namespace std;
using namespace workflow::ast::modules;
using namespace workflow::ast::statements;
using namespace workflow::ast::types;


namespace workflow::ast::modules {
    /// <summary>
    /// 模块
    /// </summary>
    class SHARED_LIB_API Module :public Statement {

    public:
        static constexpr const char* className = CLASS_NAME_MODULE;

        /// <summary>
        /// 模块名称
        /// </summary>
        string name;

        /// <summary>
        /// 模块变量列表
        /// </summary>
        map<string, Object*> variables;

        /// <summary>
        /// 模块中的语句
        /// </summary>
        Statement* body = nullptr;

        /// <summary>
        /// 函数列表
        /// </summary>
        map<string, FunctionDefinition*> functions;

        /// <summary>
        /// 包含的子模块列表
        /// </summary>
        map<string, Module*> modules;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="name"></param>
        Module(string name);

        /// <summary>
        /// 析构函数
        /// </summary>
        ~Module();

        /// <summary>
        /// 执行语句
        /// </summary>
        virtual void execute(Context* context);

        /// <summary>
        /// 获取对象名称
        /// </summary>
        /// <returns></returns>
        virtual string getClassName() const;

        /// <summary>
        /// 向模块中添加语句
        /// </summary>
        /// <param name="statement"></param>
        void addStatement(Statement* statement);

        /// <summary>
        /// 向模块中添加函数
        /// </summary>
        /// <param name="name"></param>
        /// <param name="function"></param>
        // void addFunction(string name, FunctionDefinition* function);

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);

    };
}
