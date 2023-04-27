#include "executeThread.h"

using namespace std;
using namespace workflow::ast;
using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;
using namespace workflow::ast::types;

namespace workflow::ast::executors {

    /// <summary>
    /// 
    /// </summary>
    ExecuteThread::ExecuteThread() :executeMode(ExecuteMode::Release) {}

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="statement">执行器要执行的脚本</param>
    ExecuteThread::ExecuteThread(Statement* statement) :executeMode(ExecuteMode::Release) {
        this->executor = new Executor(statement);
    }

    /// <summary>
    /// 析构函数
    /// </summary>
    ExecuteThread::~ExecuteThread() {
        if (this->thread != nullptr) {
            delete this->thread;
        }

        if (this->executor != nullptr) {
            delete this->executor;
        }
    }

    /// <summary>
    /// 执行线程
    /// </summary>
    void ExecuteThread::execute(ExecuteMode executeMode) {
        if (this->thread == nullptr) {
            //
            //this->threadStopFlag = false;

            //
            this->executeMode = executeMode;
            this->thread = new std::thread(&ExecuteThread::run, this);
        }
    }

    /// <summary>
    /// 执行脚本
    /// </summary>
    void ExecuteThread::run() {
        // cout << "子线程 run" << endl;
        this->executor->execute(this->executeMode);
    }

    /// <summary>
    /// debug执行模式下，执行到下一个语句
    /// </summary>
    void ExecuteThread::nextStatement() {
        if (this->executor != nullptr) {
            // 设置单步执行
            this->executor->context->debugMode = DebugMode::NextStatement;
            // 解除线程阻塞
            this->executor->context->conditionVariable.notify_all();
            //this->thread->join();
        }
    }

    /// <summary>
    /// debug执行模式下，继续执行
    /// </summary>
    void ExecuteThread::continueExecute() {
        // 设置继续执行
        this->executor->context->debugMode = DebugMode::Continue;
        // 解除线程阻塞
        this->executor->context->conditionVariable.notify_all();
    }

    /// <summary>
    /// 等待运行结束
    /// </summary>
    void ExecuteThread::waitStop() {
        if (this->thread != nullptr) {
            this->thread->join(); // 等待子线程完成
        }
    }

    /// <summary>
    /// 添加断点
    /// </summary>
    void ExecuteThread::addBreakpoint(Statement* statement) {
        this->executor->addBreakpoint(statement);
    }

    /// <summary>
    /// 添加断点
    /// </summary>
    void ExecuteThread::addBreakpoint(Expression* expression) {
        this->executor->addBreakpoint(expression);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    map<string, Object*> ExecuteThread::getVariables() {
        return this->executor->getVariables();
    }

}