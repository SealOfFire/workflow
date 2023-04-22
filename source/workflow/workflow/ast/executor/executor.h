#pragma once

#include "../common.h"
#include "../statements/statement.h"
#include "context.h"

using namespace workflow::ast;
using namespace workflow::ast::statements;

namespace workflow::ast::executor {

    /// <summary>
    /// 执行器
    /// </summary>
    class Executor {
    public:

        /// <summary>
        ///  执行环境
        /// </summary>
        Context* context;

        /// <summary>
        /// 执行的语句
        /// 语句时容器类型时，就是多行语句
        /// </summary>
        Statement *statement;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="statement"></param>
        Executor(Statement *statement);

        /// <summary>
        /// 析构函数
        /// </summary>
        ~Executor();

        /// <summary>
        /// 执行语句
        /// </summary>
        /// <param name="playMode">debug/release</param>
        void execute(ExecuteMode executeMode);

        void operator()(Statement *statement);

        /// <summary>
        /// 语句执行前的回调
        /// TODO 可能不需要
        /// </summary>
        /// <param name="variables">进入当前语句时的变量列表</param>
        void executeBefore_Callback(map<string, Object *> variables);

        /// <summary>
        /// 语句执行后的回调
        /// TODO 可能不需要
        /// </summary>
        /// <param name="variables">离开当前语句时的变量列表</param>
        void executeAfter_Callback(map<string, Object *> variables);

    private:

    };

}