//#include <Python.h>
#include <iostream>
#include <Python.h>
#include "test.h"

namespace workflow::framework {
    Test::Test() {
        std::cout << "aaa" << std::endl;
    }

    void Test::init() {
        //SetDllDirectory();

        //Py_SetPythonHome(L"C:\\Users\\SealO\\.conda\\envs\\python310");
        char* home;
        wchar_t* homt = Py_GetPythonHome();
        //

        Py_Initialize();

        // TODO python home

        if (!Py_IsInitialized()) {
            std::cout << "python 初始化出错" << std::endl;
            return;
        }

        int value = 0;
        value = PyRun_SimpleString("import sys");
        //value = PyRun_SimpleString("import json5");
        PyRun_SimpleString("sys.path.append(\"D:/MyProgram/github/workflow/source/workflow/workflow/scripts\")");
        PyRun_SimpleString("print(\"aaaa\")");

        // 调用python文件名，不需要写后缀
        PyObject* pModule = PyImport_ImportModule("sayhello");
        if (!pModule) {
            PyErr_Print();
            std::cout << "没找到模块 sayhello" << std::endl;
            return;
        }

        // 调用的函数名
        PyObject* pFunc = PyObject_GetAttrString(pModule, "say");
        if (!pFunc || !PyCallable_Check(pFunc)) {
            PyErr_Print();
            std::cout << "没找到函数 say" << std::endl;
            return;
        }

        PyObject_CallObject(pFunc, NULL);

        PyObject* pFunc2 = PyObject_GetAttrString(pModule, "additionFc");
        PyObject* pArgs = PyTuple_New(2);
        PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 2)); // int 类型的值2
        PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 4)); // int 类型值4

        PyObject* pReturn = PyEval_CallObject(pFunc2, pArgs);

        int nResult;
        PyArg_Parse(pReturn, "i", &nResult);
        std::cout << "result:" << nResult << std::endl;

        //Py_DECREF(pFunc2);
        Py_CLEAR(pFunc2);

        //Py_DECREF(pFunc);
        Py_CLEAR(pFunc);

        //Py_DECREF(pArgs);
        Py_CLEAR(pArgs);

        //Py_DECREF(pReturn);
        Py_CLEAR(pReturn);

        //Py_DECREF(pModule);
        Py_CLEAR(pModule);

        // 释放python
        Py_Finalize();

        int debug = 0;
        debug++;
    }
}