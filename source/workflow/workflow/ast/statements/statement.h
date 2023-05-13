#pragma once

#include <string>
#include <map>
#include <iostream>
#include "statements.h"
#include "../executors/context.h"

using namespace std;
using namespace workflow::ast::executors;

namespace workflow::ast::statements {

    /// <summary>
    /// 语句
    /// </summary>
    class SHARED_LIB_API Statement {

    public:
        static constexpr const char* className = CLASS_NAME_STATEMENT;

        /// <summary>
        /// 断点
        /// </summary>
        bool breakpoint = false;

        /// <summary>
        /// 当前语句的父节点语句
        /// </summary>
        Statement* parent = nullptr;

        /// <summary>
        /// 执行语句
        /// </summary>
        /// <param name="env"></param>
        void run(executors::Context* context);

        /// <summary>
        /// 每个脚本子类自己实现执行脚本时的功能
        /// </summary>
        virtual void execute(executors::Context* context);

        /// <summary>
        /// 获取对象名称
        /// </summary>
        /// <returns></returns>
        virtual string getClassName() const;

        /// <summary>
        /// debug模式运行时的处理
        /// </summary>
        virtual void debugProcess(executors::Context* context);

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(executors::Context* context);
    };
}