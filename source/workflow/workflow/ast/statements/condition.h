#pragma once

#include "statement.h"
#include "../expressions/expression.h"

using namespace std;
using namespace workflow::ast::executors;
using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;

namespace workflow::ast::statements {

    class SHARED_LIB_API Condition : public Statement {
    public:
        static constexpr const char* className = CLASS_NAME_CONDITION;

        /// <summary>
        /// 条件表达式
        /// </summary>
        Expression* test;

        /// <summary>
        /// 条件结果位true时运行
        /// </summary>
        Statement* body;

        /// <summary>
        /// 
        /// </summary>
        Statement* orelse;

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
