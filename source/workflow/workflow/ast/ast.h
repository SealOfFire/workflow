#pragma once
#include <mutex>
#include <condition_variable>
#include "executor/executor.h"

using namespace workflow::ast;

namespace workflow::ast {

    /// <summary>
    /// 执行脚本
    /// </summary>
    void play(Statement* statement);

    void stop();

    void aa(Statement* statement);

}