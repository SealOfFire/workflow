#pragma once
#include "../common.h"
#include "expression.h"
#include "../types/object.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {
    /// <summary>
    /// 比较运算
    /// </summary>
    class SHARED_LIB_API BinaryOperator : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_BINARY_OPERATOR;

        /// <summary>
        /// 创建一个双目运算表达式
        /// </summary>
        /// <param name="left">左表达式</param>
        /// <param name="op">运算符</param>
        /// <param name="right">右表达式</param>
        BinaryOperator(Expression* left, Operator op, Expression* right);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        Object* execute(Context* context);

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);

    private:

        /// <summary>
        /// 运算符
        /// </summary>
        Operator op;

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