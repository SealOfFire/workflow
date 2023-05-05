#include "executor.h"
#include <Python.h>

namespace workflow::framework::executors {

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="statement">需要执行的语句</param>
    Executor::Executor(Statement* statement) :workflow::ast::executors::Executor(statement) { }

    /// <summary>
    /// 初始化python运行环境
    /// </summary>
    void Executor::InitializePython() {

        // TODO 本地python
        //Py_SetPythonHome(L"C:\\Users\\SealO\\.conda\\envs\\python310");
        char* home;
        wchar_t* homt = Py_GetPythonHome();

        // 初始化python运行环境
        Py_Initialize();

        if (!Py_IsInitialized()) {
            // TODO 最后改成异常
            std::cout << "python 初始化出错" << std::endl;
            return;
        }

        // 添加python环境路径
        PyRun_SimpleString("import sys");
        for (std::string path : this->pythonPaths) {
            std::string append("sys.path.append(\'" + path + "\')");
            //std::cout << "python path:" << append << std::endl;
            PyRun_SimpleString(append.c_str());
        }

    }

    /// <summary>
    /// 
    /// </summary>
    void Executor::ReleasePython() {
        // TODO
        // 释放python
        Py_Finalize();
    }

    /// <summary>
    /// TODO 初始化lua
    /// </summary>
    void Executor::InitializeLua() {

        this->luaState = luaL_newstate();

        // 打开lua state的所有lua标准库
        luaL_openlibs(this->luaState);

        luaL_dofile(this->luaState, "D:/MyProgram/github/workflow/source/workflow/workflow/scripts/test.lua");

        lua_getglobal(this->luaState, "TestFunction");

        lua_pushnumber(this->luaState, 10);
        lua_pushnumber(this->luaState, 20);

        lua_pcall(this->luaState, 2, 1, 0);

        int result = (int)lua_tonumber(this->luaState, -1);

        lua_pop(this->luaState, 1);

    }

    /// <summary>
    /// 
    /// </summary>
    void Executor::ReleaseLua() {
        // TODO
        lua_close(this->luaState);
    }

    /// <summary>
    /// 执行
    /// </summary>
    /// <param name="executeMode"></param>
    void Executor::execute(ExecuteMode executeMode) {
        this->InitializePython();
        this->InitializeLua();
        // 
        workflow::ast::executors::Executor::execute(executeMode);

        //
        this->ReleasePython();
        this->ReleaseLua();
    }
}