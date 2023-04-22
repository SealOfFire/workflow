#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include "executor.h"

using namespace std;
using namespace workflow::ast;

namespace workflow::ast::executor {

    /// <summary>
    /// 执行流程线程
    /// </summary>
    class ExecuteThread {
    public:
        ExecuteThread(Statement *statement);

        ~ExecuteThread();

        /// <summary>
        /// 执行脚本
        /// </summary>
        /// <param name="executeMode"></param>
        void execute(ExecuteMode executeMode);

        /// <summary>
        ///  执行到下一个语句
        /// </summary>
        void nextStatement();

        /// <summary>
        /// 继续执行
        /// </summary>
        void continueExecute();

        /*
        void nextStatement();
        void nextProcess();
        void continueExecute();
        void stopExecute();
        void changeVariable();
        */

        /// <summary>
        /// 等待运行结束
        /// </summary>
        void waitStop();

    private:
        //std::mutex mutex;
        //std::condition_variable conditionVariable;

        std::thread *thread = nullptr;

        //bool threadStopFlag = true;

        /// <summary>
        /// 执行模式
        /// </summary>
        ExecuteMode executeMode;

        /// <summary>
        /// 脚本的执行器
        /// </summary>
        Executor *executor = nullptr;

        /// <summary>
        /// 执行脚本
        /// </summary>
        void run();
    };
}

// https://www.freesion.com/article/32321338069/
// https://www.stubbornhuang.com/1766/