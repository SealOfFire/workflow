#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "modules.h"
#include "../expressions/expression.h"
#include "../types/object.h"
#include "../statements/statement.h"

using namespace std;
using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;

namespace workflow::ast::modules {

    /// <summary>
    /// 函数定义
    /// </summary>
    class FunctionDefinition : public Statement {
    public:
        static constexpr const char* className = CLASS_NAME_FUNCTION_DEF;

        /// <summary>
        /// 函数名称
        /// </summary>
        string name;

        /// <summary>
        /// 模块变量列表
        /// </summary>
        map<string, Object*> variables;

        /// <summary>
        /// 模块中的语句
        /// </summary>
        vector<Statement*> body;

        /// <summary>
        /// 返回值表达式
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        Object* returns = nullptr;

        //Module* parent = nullptr;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="name"></param>
        FunctionDefinition(string name);

        /// <summary>
        /// 析构函数
        /// </summary>
        ~FunctionDefinition();

        /// <summary>
        /// 执行语句
        /// </summary>
        virtual void execute(Context* context);

        /// <summary>
        /// 函数被调用时的执行
        /// </summary>
        /// <param name="context"></param>
        virtual void call(Context* context);

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
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}