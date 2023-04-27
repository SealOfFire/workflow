#pragma once

#include "statement.h"
#include "../expressions/expression.h"

using namespace std;
using namespace workflow::ast::executors;
using namespace workflow::ast::expressions;

namespace workflow::ast::statements {
    /// <summary>
    /// 循环
    /// </summary>
    class SHARED_LIB_API While :public Statement {

    public:
        static constexpr const char* className = CLASS_NAME_WHILE;

        /// <summary>
        /// 条件表达式
        /// </summary>
        Expression* test;

        /// <summary>
        /// 条件结果位true时运行
        /// </summary>
        Statement* body = nullptr;

        While(Expression* test);

        /// <summary>
        /// 
        /// </summary>
        void execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}
