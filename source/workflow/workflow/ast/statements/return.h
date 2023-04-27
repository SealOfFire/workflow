#pragma once

#include "statement.h"
#include "../expressions/expression.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;

namespace workflow::ast::statements {

    /// <summary>
    /// 函数返回
    /// </summary>
    class SHARED_LIB_API Return :public Statement {
    public:
        static constexpr const char* className = CLASS_NAME_RETURN;

        Expression* value = nullptr;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name=""></param>
        Return(Expression* value);

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