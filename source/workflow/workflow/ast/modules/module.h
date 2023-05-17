#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "modules.h"
#include "functionDefinition.h"
#include "../variables.h"
#include "../statements/statement.h"
#include "../types/object.h"
#include "../../exportLib.h"

//using namespace workflow::ast::modules;

namespace workflow::ast::modules {
    /// <summary>
    /// 模块
    /// </summary>
    class SHARED_LIB_API Module :public statements::Statement {

    public:
        static constexpr const char* className = CLASS_NAME_MODULE;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="name"></param>
        Module(std::string name);

        /// <summary>
        /// 析构函数
        /// </summary>
        ~Module();

        /// <summary>
        /// 执行语句
        /// </summary>
        virtual void execute(executors::Context* context);

        /// <summary>
        /// 获取对象名称
        /// </summary>
        /// <returns></returns>
        virtual string getClassName() const;

        /// <summary>
        /// 向模块中添加语句
        /// </summary>
        /// <param name="statement"></param>
        void addStatement(statements::Statement* statement);

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
        virtual string toScriptCode(executors::Context* context);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        bool hasChildModule(std::string name);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        Module* getChildModule(std::string name);


        bool hasFunction(std::string name);
        FunctionDefinition* getFunction(std::string name);
        void setFunction(std::string name, FunctionDefinition* function);

        bool hasVariable(std::string name);
        types::Object* getVariable(std::string name);
        void setVariable(std::string name, types::Object* value);
        void removeVariable(std::string name);
        Variables* getVariables();

    protected:

        /// <summary>
        /// 模块名称
        /// </summary>
        std::string name;

        /// <summary>
        /// 模块变量列表
        /// </summary>
        //std::map<std::string, types::Object*> variables;
        Variables variables;

        /// <summary>
        /// 模块中的语句
        /// </summary>
        //statements::Statement* body = nullptr;
        std::vector<statements::Statement*> body;

        /// <summary>
        /// 包含的子模块列表
        /// </summary>
        std::map<std::string, Module*> childModules;

        /// <summary>
        /// 函数列表
        /// </summary>
        std::map<std::string, FunctionDefinition*> functions;

    };
}
