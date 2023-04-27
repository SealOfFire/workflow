#pragma once

#include <executors/context.h>
#include <expressions/expression.h>
#include <types/object.h>
#include "../../exportLib.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::expressions;
using namespace workflow::ast::types;

namespace workflow::framework::expressions {

    /// <summary>
    /// python脚本构成的表达式
    /// </summary>
    class SHARED_LIB_API PyExpression : public Expression {
    public:

        /// <summary>
        /// 表达式脚本
        /// </summary>
        std::string value;

        /// <summary>
        /// 每个脚本子类自己实现执行脚本时的功能
        /// </summary>
        /// <returns>返回指向结果的指针</returns>
        virtual Object* execute(Context* context);

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual std::string toScriptCode(Context* context);
    };
}