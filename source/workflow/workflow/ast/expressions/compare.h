#pragma once
#include "expression.h"

namespace workflow::ast::expressions {
    /// <summary>
    /// 比较运算
    /// </summary>
    class SHARED_LIB_API Compare : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_COMPARE;

        Compare(Expression* left, CompareOperator compareOperator, Expression* right);

        types::Object* execute(Context* context);

        virtual std::string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual std::string toScriptCode(Context* context);

    protected:

        /// <summary>
        /// 运算符
        /// </summary>
        CompareOperator compareOperator;

        /// <summary>
        /// 左表达式
        /// </summary>
        Expression* left = nullptr;

        /// <summary>
        /// 右表达式
        /// </summary>
        Expression* right = nullptr;

    };
}