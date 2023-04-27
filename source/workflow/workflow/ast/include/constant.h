#pragma once

#include "expression.h"

using namespace std;
using namespace workflow::ast::executor;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    /// <summary>
    /// 常量表达式
    /// </summary>
    class Constant : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_CONSTANT;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="value"></param>
        Constant(string value);

        /// <summary>
        /// 常量值
        /// </summary>
        string value;

        virtual Object* execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}