/**
 *
 */
#pragma once
#include"BaseActivity.h"
#include "../executor/ExecuteEnvironment.h"

using namespace workflow::executor;

namespace workflow::activities {

    /// <summary>
    /// 调用python编写的组件
    /// </summary>
    class PythonActivity : public BaseActivity {

    public:
        PythonActivity();
        PythonActivity(std::string title);

    protected:
        void run(ExecuteEnvironment* executeEnvironment);
    };
}