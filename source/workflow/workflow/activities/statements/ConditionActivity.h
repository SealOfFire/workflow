#pragma once
#include "../BaseActivity.h"
#include "../../parameters/Expression.h"
#include "../../executor/ExecuteEnvironment.h"


using namespace workflow::activities;
using namespace workflow::executor;
using namespace workflow::parameters;

namespace workflow::activities::statements {

    /// <summary>
    /// 条件判断组件
    /// </summary>
    class ConditionActivity :public BaseActivity {
    public:

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="condition">条件表达式</param>
        ConditionActivity(Expression2* condition);

        /// <summary>
        /// 析构函数
        /// </summary>
        ~ConditionActivity();

        /// <summary>
        /// 条件表达式，根据条件表达式计算结果来做判断
        /// </summary>
        Expression2* condition;

        BaseActivity* trueActivity;
        BaseActivity* falseActivity;

    protected:
        void run(ExecuteEnvironment* executeEnvironment);

    private:


    };
}