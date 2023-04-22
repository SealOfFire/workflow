#pragma once

#include "statement.h"
#include "../expressions/expression.h"

using namespace workflow::ast::executor;
using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;

namespace workflow::ast::statements {
    class Print :public Statement {
    public:
        static constexpr const char* className = CLASS_NAME_PRINT;

        Expression* value;

        Print(Expression* value);

        /// <summary>
        /// 执行语句
        /// </summary>
        virtual void execute(Context* context);

        /// <summary>
        /// 获取对象名称
        /// </summary>
        /// <returns></returns>
        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}