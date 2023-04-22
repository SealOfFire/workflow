#pragma once

#include <map>
#include "expression.h"
#include "../types/string.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {
    /// <summary>
    /// 调用函数
    /// TODO 无返回值的时候使用call是语句不是表达式
    /// </summary>
    class Call : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_CALL;

        /// <summary>
        /// 函数名
        /// </summary>
        string name;

        /// <summary>
        /// 输入参数列表
        /// </summary>
        map<string, Expression*> arguments;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="name">函数名</param>
        Call(string name, map<string, Expression*> arguments);


        Object* execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}