#pragma once

#include <vector>
#include "BaseActivity.h"
#include "../executor/ExecuteEnvironment.h"

using namespace workflow::executor;

namespace workflow::activities {

    /// <summary>
    /// 序列组件
    /// </summary>
    class ContainerActivity : public BaseActivity {

    public:

        /// <summary>
        /// 构造函数
        /// </summary>
        ContainerActivity();
        //ContainerActivity(string title);

        /// <summary>
        /// 析构函数
        /// </summary>
        ~ContainerActivity();

        /// <summary>
        /// 子组件列表
        /// </summary>
        std::vector<BaseActivity*> children;

    protected:
        void run(ExecuteEnvironment* executeEnvironment);
    };
}
