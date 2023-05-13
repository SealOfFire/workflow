#include "executor.h"
#include <regex>
#include <iostream>
#include <Python.h>
#include "../pyTools.h"

using namespace std;

namespace workflow::framework::executors {

    /// <summary>
    /// ���캯��
    /// </summary>
    /// <param name="statement">��Ҫִ�е����</param>
    Executor::Executor(Statement* statement) :workflow::ast::executors::Executor(statement) { 
        //this->context = new framework::executors::Context();
        //ast::executors::Executor(statement);
    }

    /// <summary>
    /// ��ʼ��python���л���
    /// </summary>
    void Executor::InitializePython() {

        // TODO ����python
        //Py_SetPythonHome(L"C:\\Users\\SealO\\.conda\\envs\\python310");
        char* home;
        wchar_t* homt = Py_GetPythonHome();

        /*PyStatus status;
        PyConfig config;
        PyConfig_InitPythonConfig(&config);*/

        // �ڳ�ʼ��֮�����sys.path
        // TODO winʹ�á�;���ָunix��mac osʹ�á�:���ָ�
        //const char separator(';');

        ////std::vector<std::wstring> paths = Executor::stringSplit(Py_GetPath(), separator);
        //std::vector<std::wstring> paths;
        //// ���python����·��
        //for (std::wstring path : this->pythonPaths) {
        //    paths.push_back(path);
        //}
        //std::wstring newPaths;
        //Executor::stringJoin(paths, separator, newPaths);
        //Py_SetPath(newPaths.c_str());

        // ��ʼ��python���л���
        Py_Initialize();
        //Py_InitializeFromConfig(&config);

        // �ڳ�ʼ��֮�����sys.path
        // ���sys.path
        for (std::string path : this->pythonPaths) {
            PyList_Append(PySys_GetObject("path"), PyUnicode_FromString(path.c_str()));
        }

        //PyConfig_Clear(&config);

        if (!Py_IsInitialized()) {
            // TODO ���ĳ��쳣
            std::cout << "python ��ʼ������" << std::endl;
            return;
        }

        //wchar_t* sysPath2 = Py_GetPath();

        // TODO winʹ�á�;���ָunix��mac osʹ�á�:���ָ�
        // Py_SetPath(sysPath);

        // wchar_t* sysPath2 = Py_GetPath();

        // ��ʼ��python��ͬģ��
        this->moduleTestExpression = createTestExpressionModule();
        this->functionTestExpression = PyObject_GetAttrString(this->moduleTestExpression, "test");
        if (!this->functionTestExpression || !PyCallable_Check(this->functionTestExpression)) {
            // TODO ��������
            //PyErr_Print();
            std::cout << "��������" << std::endl;
        }

    }

    /// <summary>
    /// 
    /// </summary>
    void Executor::ReleasePython() {
        // �ͷŹ�ͬģ��
        Py_DECREF(this->functionTestExpression);
        Py_DECREF(this->moduleTestExpression);

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