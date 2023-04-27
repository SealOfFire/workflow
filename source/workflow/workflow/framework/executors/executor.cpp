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
    /// ִ��
    /// </summary>
    /// <param name="executeMode"></param>
    void Executor::execute(ExecuteMode executeMode) {
        this->InitializePython();
        // 
        workflow::ast::executors::Executor::execute(executeMode);

        //
        // �ͷ�python
        Py_Finalize();
    }
}