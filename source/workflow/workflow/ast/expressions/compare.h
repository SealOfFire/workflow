#pragma once
#include "expression.h"
#include "../types/string.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {
    /// <summary>
    /// 比较运算
    /// </summary>
    class Compare : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_COPMARE;

        Object* execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}