#include "executor.h"

using namespace workflow::ast;
using namespace workflow::ast::executor;
using namespace workflow::ast::statements;

/// <summary>
/// 构造函数
/// </summary>
/// <param name="statement">需要执行的语句</param>
Executor::Executor(Statement *statement) : statement(statement) {
    this->context = new Context();
}

/// <summary>
/// 析构函数
/// </summary>
Executor::~Executor() {
    delete this->context;
}

/// <summary>
/// 执行
/// </summary>
/// <param name="executeMode"></param>
void Executor::execute(ExecuteMode executeMode) {

    // 执行模式 release/debug
    this->context->executeMode = executeMode;
    if (executeMode == ExecuteMode::Debug) {
        // 如果是debug模式运行。初始时，执行到第一个断点停住
        this->context->debugMode = DebugMode::Continue;
    }

    // 执行语句
    this->statement->run(this->context);

    cout << "执行结束" << endl;
}

void Executor::operator()(Statement *statement) {
    this->statement = statement;
}

/// <summary>
/// 执行语句前回调
/// TODO 可能不需要
/// </summary>
void Executor::executeBefore_Callback(map<string, Object *> variables) {
}

/// <summary>
/// 执行语句后回调
/// TODO 可能不需要
/// </summary>
void Executor::executeAfter_Callback(map<string, Object *> variables) {
}