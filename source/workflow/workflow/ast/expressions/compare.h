#pragma once
#include "expression.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {
    /// <summary>
    /// 比较运算
    /// </summary>
    class SHARED_LIB_API Compare : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_COMPARE;

        // 运算符
        CompareOperator compareOperator;

        Expression* left; // 左表达式
        Expression* right; // 右表达式

        Compare(Expression* left, CompareOperator compareOperator, Expression* right);

        Object* execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}