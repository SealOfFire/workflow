#pragma once

#include "expression.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    /// <summary>
    /// 创建一个list数据对象
    /// </summary>
    class SHARED_LIB_API Subscript : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_EXPR_SUBSCRIPT;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        /// <param name="slice"></param>
        Subscript(Expression* value, Expression* slice);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        virtual Object* execute(executors::Context* context);

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(executors::Context* context);

        Expression* value;
        Expression* slice;

    };

}