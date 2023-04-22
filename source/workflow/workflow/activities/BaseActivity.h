/**
 *
 */
#pragma once
#include <vector>
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include "../parameters/Property.h"
#include "../lua/lua.hpp"
#include "../executor/ExecuteEnvironment.h"

using namespace workflow::executor;

namespace workflow::activities {
    /// <summary>
    /// 组件基类
    /// </summary>
    class BaseActivity {
    public:
        /// <summary>
        /// 组件id
        /// </summary>
        boost::uuids::uuid identity;

        /// <summary>
        /// 组件标题
        /// </summary>
        std::string title = "基础组件";

        /// <summary>
        /// 运行前延时（毫秒）
        /// </summary>
        int beforeDelay = 300;

        /// <summary>
        /// 运行后延时（毫秒）
        /// </summary>
        int afterDelay = 300;

        /// <summary>
        /// 错误执行
        /// </summary>
        bool errorContinueRun = false;

        // 参数列表

        // TODO 组件是否是正常运行结束
        // TODO 错误运行时的错误信息。会有多个错误信息。这里需要列表保存

        /// <summary>
        /// 构造函数
        /// </summary>
        BaseActivity();
        BaseActivity(std::string title);

        /// <summary>
        /// 组件执行
        /// </summary>
        virtual void execute(ExecuteEnvironment* executeEnvironment);

    protected:
        virtual void runBefore(ExecuteEnvironment* executeEnvironment);
        virtual void run(ExecuteEnvironment* executeEnvironment);
        virtual void runAfter(ExecuteEnvironment* executeEnvironment);

    };
}