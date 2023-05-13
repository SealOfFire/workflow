#include "executor.h"
#include <regex>
#include <iostream>
#include <Python.h>
#include "../pyTools.h"

using namespace std;

namespace workflow::framework::executors {

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="statement">需要执行的语句</param>
    Executor::Executor(Statement* statement) :workflow::ast::executors::Executor(statement) { 
        //this->context = new framework::executors::Context();
        //ast::executors::Executor(statement);
    }

    /// <summary>
    /// 初始化python运行环境
    /// </summary>
    void Executor::InitializePython() {

        // TODO 本地python
        //Py_SetPythonHome(L"C:\\Users\\SealO\\.conda\\envs\\python310");
        char* home;
        wchar_t* homt = Py_GetPythonHome();

        /*PyStatus status;
        PyConfig config;
        PyConfig_InitPythonConfig(&config);*/

        // 在初始化之情添加sys.path
        // TODO win使用”;“分割。unix和mac os使用”:“分割
        //const char separator(';');

        ////std::vector<std::wstring> paths = Executor::stringSplit(Py_GetPath(), separator);
        //std::vector<std::wstring> paths;
        //// 添加python环境路径
        //for (std::wstring path : this->pythonPaths) {
        //    paths.push_back(path);
        //}
        //std::wstring newPaths;
        //Executor::stringJoin(paths, separator, newPaths);
        //Py_SetPath(newPaths.c_str());

        // 初始化python运行环境
        Py_Initialize();
        //Py_InitializeFromConfig(&config);

        // 在初始化之后添加sys.path
        // 添加sys.path
        for (std::string path : this->pythonPaths) {
            PyList_Append(PySys_GetObject("path"), PyUnicode_FromString(path.c_str()));
        }

        //PyConfig_Clear(&config);

        if (!Py_IsInitialized()) {
            // TODO 最后改成异常
            std::cout << "python 初始化出错" << std::endl;
            return;
        }

        //wchar_t* sysPath2 = Py_GetPath();

        // TODO win使用”;“分割。unix和mac os使用”:“分割
        // Py_SetPath(sysPath);

        // wchar_t* sysPath2 = Py_GetPath();

        // 初始化python共同模块
        this->moduleTestExpression = createTestExpressionModule();
        this->functionTestExpression = PyObject_GetAttrString(this->moduleTestExpression, "test");
        if (!this->functionTestExpression || !PyCallable_Check(this->functionTestExpression)) {
            // TODO 函数错误
            //PyErr_Print();
            std::cout << "函数错误" << std::endl;
        }

    }

    /// <summary>
    /// 
    /// </summary>
    void Executor::ReleasePython() {
        // 释放共同模块
        Py_DECREF(this->functionTestExpression);
        Py_DECREF(this->moduleTestExpression);

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

    std::vector<std::wstring> Executor::stringSplit(const std::wstring& str, char delim) {
        std::wstring s;
        s.append(1, delim);
        //std::regex reg(s);
        std::wregex reg(s);
        //std::vector<std::wstring> elems(std::sregex_token_iterator(str.begin(), str.end(), reg, -1), std::sregex_token_iterator());
        std::vector<std::wstring> elems(std::wsregex_token_iterator(str.begin(), str.end(), reg, -1), std::wsregex_token_iterator());

        return elems;
    }

    void Executor::stringJoin(std::vector<std::wstring> list, char delim, std::wstring& s) {
        for (std::vector<std::wstring>::const_iterator ii = list.begin(); ii != list.end(); ++ii)
        {
            s += (*ii);
            if (ii + 1 != list.end()) {
                s += delim;
            }
        }
    }

}