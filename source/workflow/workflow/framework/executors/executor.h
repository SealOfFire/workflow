#pragma once
#include <vector>
#include <executors/executor.h>

namespace workflow::framework::executors {

    /// <summary>
    /// 执行器
    /// </summary>
    class Executor : public workflow::ast::executors::Executor {
    private:

    public:

        /// <summary>
        /// 运行时的python路径
        /// </summary>
        std::vector<std::string> pythonPaths;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="statement"></param>
        Executor(Statement* statement);

        /// <summary>
        /// 初始化python运行环境
        /// </summary>
        void InitializePython();

        /// <summary>
        /// 执行语句
        /// </summary>
        /// <param name="playMode">debug/release</param>
        void execute(ExecuteMode executeMode);
    };
}