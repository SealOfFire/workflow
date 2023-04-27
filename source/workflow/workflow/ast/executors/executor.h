#pragma once

#include "context.h"
#include "../common.h"
#include "../expressions/expression.h"
#include "../statements/statement.h"
#include "../types/object.h"
#include "../../exportLib.h"

using namespace workflow::ast;
using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;
using namespace workflow::ast::types;

namespace workflow::ast::executors {

    /// <summary>
    /// 执行器
    /// </summary>
    class SHARED_LIB_API Executor {
    public:

        /// <summary>
        ///  执行环境
        /// </summary>
        Context* context;

        /// <summary>
        /// 执行的语句
        /// 语句时容器类型时，就是多行语句
        /// </summary>
        Statement* statement = nullptr;

        /// <summary>
        /// 空构造函数
        /// </summary>
        Executor();

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="statement"></param>
        Executor(Statement* statement);

        /// <summary>
        /// 析构函数
        /// </summary>
        ~Executor();

        /// <summary>
        /// 执行语句
        /// </summary>
        /// <param name="playMode">debug/release</param>
        virtual void execute(ExecuteMode executeMode);

        /// <summary>
        /// 添加断点
        /// </summary>
        void addBreakpoint(Statement* statement);

        /// <summary>
        /// 添加断点
        /// </summary>
        void addBreakpoint(Expression* expression);

        // TODO 删除断点
        // TODO 获取断点列表

        /// <summary>
        /// 进入断点后。获取当前局域变量列表
        /// </summary>
        /// <returns></returns>
        map<string, Object*> getVariables();

        void operator()(Statement* statement);

        /// <summary>
        /// 语句执行前的回调
        /// TODO 可能不需要
        /// </summary>
        /// <param name="variables">进入当前语句时的变量列表</param>
        void executeBefore_Callback(map<string, Object*> variables);

        /// <summary>
        /// 语句执行后的回调
        /// TODO 可能不需要
        /// </summary>
        /// <param name="variables">离开当前语句时的变量列表</param>
        void executeAfter_Callback(map<string, Object*> variables);

    private:

    };

}