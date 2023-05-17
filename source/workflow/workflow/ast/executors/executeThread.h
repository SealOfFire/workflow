#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include "executor.h"
#include "../expressions/expression.h"
#include "../statements/statement.h"
#include "../types/object.h"
#include "../../exportLib.h"

using namespace std;
using namespace workflow::ast;
using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;
using namespace workflow::ast::types;

namespace workflow::ast::executors {

    /// <summary>
    /// 在子线程上运行的执行器
    /// </summary>
    class SHARED_LIB_API ExecuteThread {
    public:

        /// <summary>
        /// 
        /// </summary>
        ExecuteThread();

        /// <summary>
        /// 创建一个在子线程上运行的执行器
        /// </summary>
        /// <param name="statement">执行器要执行的脚本</param>
        ExecuteThread(Statement* statement);

        ~ExecuteThread();

        /// <summary>
        /// 执行脚本
        /// </summary>
        /// <param name="executeMode">执行模式 release/debug</param>
        void execute(ExecuteMode executeMode);

        /// <summary>
        ///  debug执行模式下，执行到下一个语句
        /// </summary>
        void nextStatement();

        /// <summary>
        /// debug执行模式下，继续执行
        /// </summary>
        void continueExecute();

        /// <summary>
        /// 添加断点
        /// </summary>
        void addBreakpoint(Statement* statement);

        /// <summary>
        /// 添加断点
        /// </summary>
        void addBreakpoint(Expression* expression);

        /// <summary>
        /// 进入断点后。获取当前局域变量列表
        /// </summary>
        /// <returns></returns>
        //map<string, Object*> getVariables();

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

    protected:
        //std::mutex mutex;
        //std::condition_variable conditionVariable;

        std::thread* thread = nullptr;

        //bool threadStopFlag = true;

        /// <summary>
        /// 执行模式
        /// </summary>
        ExecuteMode executeMode;

        /// <summary>
        /// 脚本的执行器
        /// </summary>
        Executor* executor = nullptr;

        /// <summary>
        /// 执行脚本
        /// </summary>
        void run();
    };
}

// https://www.freesion.com/article/32321338069/
// https://www.stubbornhuang.com/1766/