#pragma once

#include "expression.h"
#include "../types/string.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {
    /// <summary>
    /// 变量表达式
    /// </summary>
    class Name : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_NAME;

        /// <summary>
        /// 变量的标识
        /// </summary>
        string id;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="id"></param>
        Name(string id);

        Object* execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}