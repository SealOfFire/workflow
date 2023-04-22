#pragma once

#include "expression.h"

using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    /// <summary>
    /// lua表达式
    /// </summary>
    class Lua : public Expression {
    public:
        virtual Object* execute(Context* context);

        virtual string getClassName() const;
    };
}