#include"Expression.h"

using namespace workflow::activities;
using namespace workflow::executor;
using namespace workflow::parameters;

Expression2::Expression2(string value) :value(value) {}

/// <summary>
/// 计算表达式
/// </summary>
/// <param name="exeEnv"></param>
void Expression2::calculate(ExecuteEnvironment* executeEnvironment) {}
