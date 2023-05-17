#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "modules.h"
#include "../variables.h"
#include "../expressions/expression.h"
#include "../statements/statement.h"
#include "../types/object.h"
#include "../../exportLib.h"

namespace workflow::ast::modules {

    /// <summary>
    /// 函数定义
    /// </summary>
    class SHARED_LIB_API FunctionDefinition : public statements::Statement {
    public:
        static constexpr const char* className = CLASS_NAME_FUNCTION_DEF;

        /// <summary>
        /// 模块变量列表
        /// </summary>
        Variables variables;

        /// <summary>
        /// 返回值表达式
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        types::Object* returns = nullptr;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="name"></param>
        FunctionDefinition(std::string name);

        /// <summary>
        /// 析构函数
        /// </summary>
        ~FunctionDefinition();

        /// <summary>
        /// 执行语句
        /// 定义函数
        /// </summary>
        virtual void execute(executors::Context* context);

        /// <summary>
        /// 函数被调用时的执行
        /// </summary>
        /// <param name="context"></param>
        virtual void call(executors::Context* context);

        /// <summary>
        /// 获取对象名称
        /// </summary>
        /// <returns></returns>
        virtual std::string getClassName() const;

        /// <summary>
        /// 向模块中添加语句
        /// </summary>
        /// <param name="statement"></param>
        void addStatement(statements::Statement* statement);

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(executors::Context* context);

        //bool hasVariable(std::string name);
        //void setVariable(std::string name, types::Object* value);

    protected:

        /// <summary>
        /// 函数名称
        /// </summary>
        std::string name;

        /// <summary>
        /// 模块变量列表
        /// </summary>
        //std::map<std::string, types::Object*> variables;


        /// <summary>
        /// 模块中的语句
        /// </summary>
        std::vector<statements::Statement*> body;
    };
}