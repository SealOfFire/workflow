#pragma once

#include "expression.h"

namespace workflow::ast::expressions {

    /// <summary>
    /// 直接返回object值的表达式
    /// </summary>
    class SHARED_LIB_API Value : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_EXPR_VALUE;

        /// <summary>
        /// 变量的标识
        /// </summary>
        types::Object* value;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="id"></param>
        Value(types::Object* value);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        virtual ast::types::Object* execute(executors::Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(executors::Context* context);
    };

}