#pragma once
#include "statement.h"
#include "../expressions/expression.h"

namespace workflow::ast::statements {

    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API For : public Statement {
    public:
        static constexpr const char* className = CLASS_NAME_FOR;

        For(expressions::Expression* target, expressions::Expression* iteration, Statement* body);

        void execute(executors::Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(executors::Context* context);

    protected:

        /// <summary>
        /// 条件结果位true时运行
        /// </summary>
        Statement* body = nullptr;

        expressions::Expression* iteration = nullptr;
        expressions::Expression* target = nullptr;

    };

}