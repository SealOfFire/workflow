#pragma once

#include "expression.h"

using namespace workflow::ast;

namespace workflow::ast::expressions {

    /// <summary>
    /// bool类型表达式
    /// </summary>
    class BoolOperateExpression : public Expression {
    public:
        Expression* left;
        Expression* right;

        virtual Object* execute(Context* context);

        virtual string getClassName() const;
    };
}