#include "ConditionActivity.h"

using namespace workflow::activities;
using namespace workflow::activities::statements;
using namespace workflow::parameters;

ConditionActivity::ConditionActivity(Expression2* condition) :BaseActivity("条件判断组件"), condition(condition) {
    this->trueActivity = nullptr;
    this->falseActivity = nullptr;
}

/// <summary>
/// 析构函数
/// </summary>
ConditionActivity::~ConditionActivity() {
    delete this->condition;

    if (this->trueActivity != nullptr) {
        delete this->trueActivity;
    }

    if (this->falseActivity != nullptr) {
        delete this->falseActivity;
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="execEnv"></param>
void ConditionActivity::run(ExecuteEnvironment* executeEnvironment) {

    // 计算表达式
    this->condition->calculate(executeEnvironment);

    // 根绝表达式结果执行不同的子组件
    if (this->condition->result == "true") {
        this->trueActivity->execute(executeEnvironment);
    }
    else {
        this->falseActivity->execute(executeEnvironment);
    }
}