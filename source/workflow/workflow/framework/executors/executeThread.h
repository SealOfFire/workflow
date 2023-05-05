#pragma once
#include <executors/executeThread.h>

using namespace workflow::ast::statements;

namespace workflow::framework::executors {

    /// <summary>
    /// 执行器
    /// </summary>
    class ExecuteThread : public workflow::ast::executors::ExecuteThread {
    public:
        ExecuteThread(Statement* statement);

        /// <summary>
        /// 添加python运行时路径
        /// </summary>
        /// <param name="path"></param>
        void appendPythonPath(std::string path);

        /// <summary>
        /// 初始化python运行环境
        /// </summary>
        void InitializePython();

        
    };
}