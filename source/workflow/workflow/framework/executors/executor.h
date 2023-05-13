#pragma once
#include <wchar.h>
#include <vector>
#include <executors/executor.h>
#include "context.h"

// c++ 引用c
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace workflow::framework::executors {

    /// <summary>
    /// 执行器
    /// </summary>
    class Executor : public workflow::ast::executors::Executor {
    private:

    public:
        //framework::executors::Context* context;

        /// <summary>
        /// 运行时的python路径
        /// </summary>
        std::vector<std::string> pythonPaths;

        lua_State* luaState = nullptr;

        PyObject* moduleTestExpression;
        PyObject* functionTestExpression;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="statement"></param>
        Executor(Statement* statement);

        /// <summary>
        /// 初始化python运行环境
        /// </summary>
        void InitializePython();

        /// <summary>
        /// 初始化lua
        /// </summary>
        void InitializeLua();

        void ReleasePython();

        void ReleaseLua();

        /// <summary>
        /// 执行语句
        /// </summary>
        /// <param name="playMode">debug/release</param>
        void execute(ExecuteMode executeMode);

        static std::vector<std::wstring> stringSplit(const std::wstring& str, char delim);
        static void stringJoin(std::vector<std::wstring> list, char delim, std::wstring& s);

    };
}