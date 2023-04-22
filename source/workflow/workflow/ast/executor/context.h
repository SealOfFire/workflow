#pragma once

#include <mutex>
#include <condition_variable>
#include <string>
#include <map>
#include <vector>
#include "../common.h"
#include "variableStack.h"
//#include "../expressions/expression.h"
#include "../types/object.h"

namespace workflow::ast::expressions {
    class Expression;
}

namespace workflow::ast::modules {
    class FunctionDefinition;
    class Module;
}

using namespace std;
using namespace workflow::ast;
using namespace workflow::ast::executor;
using namespace workflow::ast::types;

namespace workflow::ast::executor {

    /// <summary>
    /// ast运行时的上下文
    /// 断点从类属性，改为上下文你中的列表
    /// </summary>
    class Context {
    public:

        /// <summary>
        /// 运行模式
        /// debug/release
        /// </summary>
        ExecuteMode executeMode;

        /// <summary>
        /// 
        /// </summary>
        DebugMode debugMode;

        /// <summary>
        /// 变量列表，容器内的语句使用同一层级的作用域变量
        /// 变量栈，
        /// 执行容器型语句的时候压入当前容器的的变量列表
        /// 执行结束后弹出参数列表
        /// </summary>
        //map<string, Object*> variables;
        VariableStack variables;

        /// <summary>
        /// 模块
        /// </summary>
        //xworkflow::ast::modules::Module* parent = nullptr;

        /// <summary>
        /// 函数列表 TODO 可删除
        /// </summary>
        map<string, workflow::ast::modules::FunctionDefinition*> functions;

        /// <summary>
        /// TODO 可删除
        /// </summary>
        map<string, workflow::ast::modules::Module*> modules;

        /// <summary>
        /// 
        /// </summary>
        workflow::ast::modules::Module* currentModule = nullptr;

        /// <summary>
        /// 错误信息列表
        /// </summary>
        vector<string> errors;

        /// <summary>
        /// 换行符
        /// </summary>
        std::string newline = "\r\n";

        /// <summary>
        /// 缩进的等级
        /// </summary>
        int indentLevel = 0;

        /// <summary>
        /// 缩进的数量
        /// </summary>
        int indentCount = 2;

        // 互斥锁
        std::mutex mutex;
        // 条件变量
        std::condition_variable conditionVariable;

    };
}