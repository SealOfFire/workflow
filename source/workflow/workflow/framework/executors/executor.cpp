#include "executor.h"
#include <Python.h>

namespace workflow::framework::executors {

    /// <summary>
    /// ���캯��
    /// </summary>
    /// <param name="statement">��Ҫִ�е����</param>
    Executor::Executor(Statement* statement) :workflow::ast::executors::Executor(statement) { }

    /// <summary>
    /// ��ʼ��python���л���
    /// </summary>
    void Executor::InitializePython() {

        // TODO ����python
        //Py_SetPythonHome(L"C:\\Users\\SealO\\.conda\\envs\\python310");
        char* home;
        wchar_t* homt = Py_GetPythonHome();

        // ��ʼ��python���л���
        Py_Initialize();

        if (!Py_IsInitialized()) {
            // TODO ���ĳ��쳣
            std::cout << "python ��ʼ������" << std::endl;
            return;
        }

        // ���python����·��
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
        // �ͷ�python
        Py_Finalize();
    }

    /// <summary>
    /// TODO ��ʼ��lua
    /// </summary>
    void Executor::InitializeLua() {

        this->luaState = luaL_newstate();

        // ��lua state������lua��׼��
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
    /// ִ��
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