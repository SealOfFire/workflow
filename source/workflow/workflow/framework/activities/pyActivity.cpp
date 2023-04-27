#include <Python.h>
#include "pyActivity.h"

namespace workflow::framework::activities {

    PyActivity::PyActivity(std::string moduleName, std::string functionName) :moduleName(moduleName), functionName(functionName) {
    }

    /// <summary>
    /// 运行语句
    /// </summary>
    /// <param name="context"></param>
    void PyActivity::executeActivity(workflow::ast::executors::Context* context) {

        // 
        if (!Py_IsInitialized()) {
            // TODO 最后改成异常
            std::cout << "python 初始化出错" << std::endl;
            return;
        }

        //PyRun_SimpleString("print(sys.path)");

        // 根据模块名导入模块
        // 调用python文件名，不需要写后缀
        PyObject* pModule = PyImport_ImportModule(this->moduleName.c_str());
        //PyObject* pModule = PyImport_ImportModule("activity");
        if (!pModule) {
            PyErr_Print();
            std::cout << "没找到模块" << this->moduleName << std::endl;
            return;
        }

        // 调用的函数名
        PyObject* pFunc = PyObject_GetAttrString(pModule, this->functionName.c_str());
        if (!pFunc || !PyCallable_Check(pFunc)) {
            PyErr_Print();
            std::cout << "没找到函数" << this->functionName.c_str() << std::endl;
            return;
        }

        // 计算模块的输入参数

        // 调用模块中的运行函数
        PyObject_CallObject(pFunc, NULL);

        // 计算模块的输出参数
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    std::string PyActivity::toScriptCode(Context* context) {
        std::string indent(context->indentCount * context->indentLevel, ' ');

        std::string output = indent + "python " + this->moduleName + "." + this->functionName + context->newline;
        context->indentLevel++;
        std::string indent2(context->indentCount * context->indentLevel, ' '); // 大括号内重新计算缩进
        output += indent + "{" + context->newline;
        for (auto [name, expr] : this->parameters) {
            output += indent2 + name + " = " + expr->toScriptCode(context) + context->newline;
        }

        output += indent + "}" + context->newline;
        context->indentLevel--;

        return output;
    }
}