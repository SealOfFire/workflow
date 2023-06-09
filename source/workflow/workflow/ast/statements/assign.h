﻿#pragma once

#include "statement.h"
#include "../expressions/expression.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::expressions;

namespace workflow::ast::statements {

    /// <summary>
    /// 赋值语句
    /// </summary>
    class SHARED_LIB_API Assign : public Statement {
    public:
        static constexpr const char* className = CLASS_NAME_ASSIGN;

        /// <summary>
        /// 构造函数
        /// </summary>
        Assign(Expression* target, Expression* value);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="env"></param>
        void execute(executors::Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(executors::Context* context);

    protected:
        /// <summary>
        /// 赋值的目标
        /// </summary>
        Expression* target;

        /// <summary>
        /// 赋值的值
        /// </summary>
        Expression* value;

    };
}