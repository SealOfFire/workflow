#pragma once

#include "expression.h"

//namespace workflow::ast {
//    class Manager;
//}

namespace workflow::ast::expressions {

    /// <summary>
    /// 常量表达式
    /// </summary>
    class SHARED_LIB_API Constant : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_CONSTANT;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="value"></param>
        Constant(string value);

        virtual types::Object* execute(executors::Context* context);

        virtual std::string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual std::string toScriptCode(executors::Context* context);

    protected:
        /// <summary>
        /// 常量值
        /// </summary>
        string value;

    };
}