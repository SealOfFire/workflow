/**
 *
 */
#pragma once
 //#include <vector>
#include "../activities/BaseActivity.h"
#include "ExecuteEnvironment.h"

using namespace  workflow::activities;
using namespace  workflow::executor;

namespace workflow::executor {

    /// <summary>
    /// 执行器
    /// </summary>
    class Executor {
    public:
        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="activity"></param>
        Executor(BaseActivity* activity);
        ~Executor();

        /// <summary>
        /// 执行器运行的activity
        /// </summary>
        BaseActivity* activity;

        /// <summary>
        /// 初始化执行器
        /// </summary>
        /// <returns>初始化是否成功</returns>
        bool Initialize();

        // TODO 运行结束时，释放初始化资源

        /// <summary>
        /// 执行流程
        /// </summary>
        void execute();

        /// <summary>
        /// 运行环境参数
        /// </summary>
        ExecuteEnvironment executeEnvironment;

    private:
        // 组件调用栈
        // std::vector<BaseActivity*> activityStack;

        //void callbackActivityBegin(BaseActivity activity);
        //void callbackActivityEnd(BaseActivity activity);
    };
}