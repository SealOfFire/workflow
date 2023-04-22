#include <thread>
#include "ast.h"
#include "executor/executor.h"

using namespace std;
using namespace workflow::ast;
using namespace workflow::ast::executor;
using namespace workflow::ast::statements;

void workflow::ast::play(Statement *statement) {
    ///Executor executor(statement);

    // 创建一个子线程
    thread childThread(aa, statement);

    // 阻塞等待子线程完成
    // childThread.join();
}

/// <summary>
/// 停止执行
/// </summary>
void workflow::ast::stop() {
}

void workflow::ast::aa(Statement *statement) {
    // 
    Executor executor(statement);

    // 执行
    executor.execute(ExecuteMode::Release);
}