/**
 *
 */
#include <boost/log/trivial.hpp>
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif
#include"Executor.h"
#include "../lua/lua.hpp"

using namespace workflow;
using namespace workflow::activities;
using namespace workflow::executor;

/// <summary>
/// 构造函数
/// </summary>
Executor::Executor(BaseActivity* activity) :activity(activity) {
    //this->activity.callbackBegin = callbackActivityBegin;
    //this->activity.callbackBegin = this->callbackActivityBegin;
}

Executor::~Executor() {
    delete this->activity;
}

/// <summary>
/// 初始化执行器
/// </summary>
/// <returns>初始化是否成功</returns>
bool Executor::Initialize() {

    //g_activityStack.clear();

    //// 初始化python解释器
    //Py_Initialize();
    //if (!Py_IsInitialized()) {
    //    BOOST_LOG_TRIVIAL(error) << "python 初始化失败";
    //    return 0;
    //}


    // 初始化lua脚本支持
    this->executeEnvironment.luaState = luaL_newstate();
    if (nullptr == this->executeEnvironment.luaState) {
        BOOST_LOG_TRIVIAL(error) << "lua 初始化失败";
    }
    else {
        // 加载相关库文件
        luaL_openlibs(this->executeEnvironment.luaState);

        lua_getglobal(this->executeEnvironment.luaState, "print");
        lua_pushstring(this->executeEnvironment.luaState, "hello world");
        lua_call(this->executeEnvironment.luaState, 1, 0);
    }



    return true;
}

void Executor::execute() {
    BOOST_LOG_TRIVIAL(info) << "-- 流程运行 开始 --";
    // 运行前压入栈
    //this->activityStack.insert(this->activityStack.begin(), &this->activity);
    this->activity->execute(&this->executeEnvironment);
    // 运行结束后移从栈移除
    //this->activityStack.erase(this->activityStack.begin());
    BOOST_LOG_TRIVIAL(info) << "-- 流程运行 完成 --";
}
