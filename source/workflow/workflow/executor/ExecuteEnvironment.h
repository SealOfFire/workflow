#pragma once
#include <vector>
//#include "../activities/BaseActivity.h"
#include "../lua/lua.hpp"

using namespace std;
//using namespace workflow::activities;

namespace workflow::activities {
    class BaseActivity;
}

namespace workflow::executor {

    /// <summary>
    /// 组件运行时的环境参数
    /// </summary>
    struct ExecuteEnvironment {
        /// <summary>
        /// 运行时组件栈
        /// </summary>
        std::vector<workflow::activities::BaseActivity*> activityStack;

        /// <summary>
        /// lua脚本支持
        /// </summary>
        lua_State* luaState;
    };
}