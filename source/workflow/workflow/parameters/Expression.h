#pragma once
#include<string>
#include "../activities/BaseActivity.h"
#include"../executor/ExecuteEnvironment.h"

using namespace std;
using namespace workflow::activities;
using namespace workflow::parameters;

namespace workflow::parameters {
    /// <summary>
    /// 表达式
    /// </summary>
    class Expression2 {
    public:
        Expression2(string value);

        /// <summary>
        /// 需要计算的表达式
        /// </summary>
        string value;

        /// <summary>
        /// 表达式计算的结果
        /// </summary>
        string result;

        /// <summary>
        /// 计算表达式
        /// </summary>
        /// <param name="exeEnv"></param>
        virtual void calculate(ExecuteEnvironment* executeEnvironment);
    };
}