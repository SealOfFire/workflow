#pragma once
#include "statement.h"

namespace workflow::ast::statements {

    /// <summary>
    /// TODO
    /// </summary>
    class Break : public Statement {
    public:
        static constexpr const char* className = CLASS_NAME_BREAK;

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}