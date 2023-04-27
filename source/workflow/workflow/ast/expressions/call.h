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
    class SHARED_LIB_API Call : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_CALL;

        /// <summary>
        /// 模块名
        /// </summary>
        string modeuleName;

        /// <summary>
        /// 函数名
        /// </summary>
        string functionName;

        /// <summary>
        /// 输入参数列表
        /// </summary>
        map<string, Expression*> arguments;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="name">函数名</param>
        Call(string functionName, map<string, Expression*> arguments);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="modeuleName"></param>
        /// <param name="functionName"></param>
        /// <param name="arguments"></param>
        Call(string modeuleName, string functionName, map<string, Expression*> arguments);

        Object* execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}