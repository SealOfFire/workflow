#include "executor.h"
#include "../exceptions/errorMessage.h"
#include "../exceptions/nullReferenceException.h"
#include "../modules/module.h"

using namespace workflow::ast;
using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;

namespace workflow::ast::executors {

    /// <summary>
    /// 
    /// </summary>
    Executor::Executor() {
        this->initializerContext();
    }

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="statement">需要执行的语句</param>
    Executor::Executor(Statement* statement) : statement(statement) {
        this->initializerContext();
    }

    /// <summary>
    /// 析构函数
    /// </summary>
    Executor::~Executor() {
        delete this->context;
    }

    /// <summary>
    /// 
    /// </summary>
    void Executor::initializerContext() {
        this->context = new Context();
        this->context->executor = this;
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

        if (this->statement == nullptr) {
            throw exceptions::NullReferenceException(this, "statement");
            //std::cout << "没有可执行的语句" << std::endl;
        }
        else
        {
            // 执行语句
            this->statement->run(this->context);
        }

        // TODO 执行结束
        cout << "执行结束" << endl;
    }

    /// <summary>
    /// 添加断点
    /// </summary>
    void Executor::addBreakpoint(Statement* statement) {
        this->context->breakpointStatements.push_back(statement);
    }

    /// <summary>
    /// 添加断点
    /// </summary>
    void Executor::addBreakpoint(Expression* expression) {
        this->context->breakpointExpressions.push_back(expression);
    }

    ///// <summary>
    ///// 
    ///// </summary>
    ///// <returns></returns>
    //map<string, Object*> Executor::getVariables() {
    //    if (this->context->currentModule != nullptr) {
    //        return this->context->currentModule->variables;
    //    }
    //    else
    //    {
    //        // TODO
    //    }
    //}

    void Executor::operator()(Statement* statement) {
        this->statement = statement;
    }

    /// <summary>
    /// 执行语句前回调
    /// TODO 可能不需要
    /// </summary>
    void Executor::executeBefore_Callback(map<string, Object*> variables) {
    }

    /// <summary>
    /// 执行语句后回调
    /// TODO 可能不需要
    /// </summary>
    void Executor::executeAfter_Callback(map<string, Object*> variables) {
    }

}