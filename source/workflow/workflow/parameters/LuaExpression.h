#pragma once
#include<string>
#include"Expression.h"

using namespace std;

namespace workflow::parameters {
    /// <summary>
    /// 表达式
    /// </summary>
    class LuaExpression : public Expression2 {
    public:
        LuaExpression(string value);

        /// <summary>
        /// 计算表达式
        /// </summary>
        /// <param name="executeEnvironment"></param>
        void calculate(ExecuteEnvironment* executeEnvironment);
    };
}