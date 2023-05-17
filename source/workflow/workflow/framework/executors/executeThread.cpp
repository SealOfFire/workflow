#include "executeThread.h"
#include "executor.h"

using namespace workflow::ast::statements;

namespace workflow::framework::executors {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="statement"></param>
    ExecuteThread::ExecuteThread(Statement* statement) {
        this->executor = new Executor(statement);
    }

    ExecuteThread::~ExecuteThread() {
        // TODO 这里delete会报错
        //delete this->executor;
    }

    void ExecuteThread::appendPythonPath(std::string path) {
        ((Executor*)this->executor)->pythonPaths.push_back(path);
    }

    void ExecuteThread::InitializePython() {
        ((Executor*)this->executor)->InitializePython();
    }
}