//#include <Python.h>
#include "pyActivity.h"
#include <types/boolean.h>
#include <types/float.h>
#include <types/integer.h>
#include <types/long.h>
#include <types/null.h>
#include <types/string.h>
#include "../types/astPyObject.h"

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
        if (!pModule) {
            PyErr_Print();
            std::cout << "没找到模块" << this->moduleName << std::endl;
            return;
        }

        // 计算模块的输入参数
        // 设置模块的全局参数
        this->setParameters(context, pModule);

        // 函数的入参
        PyObject* pArgs = this->getFunctionParameters(context);


        // 调用的函数名
        PyObject* pFunc = PyObject_GetAttrString(pModule, this->functionName.c_str());
        if (!pFunc || !PyCallable_Check(pFunc)) {
            PyErr_Print();
            std::cout << "没找到函数" << this->functionName.c_str() << std::endl;
            return;
        }

        // 调用模块中的运行函数
        PyObject_CallObject(pFunc, pArgs);

        // TODO 计算模块的输出参数


        // 释放资源
        Py_CLEAR(pArgs);

        //Py_DECREF(pFunc);
        Py_CLEAR(pFunc);

        //Py_DECREF(pModule);
        Py_CLEAR(pModule);

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

    /// <summary>
    /// 设置组件的参数
    /// </summary>
    void PyActivity::setParameters(workflow::ast::executors::Context* context, PyObject* pyModule) {
        //PyImport_GetModuleDict
        // 从模块中获取模块的所有元素
        int pyResult = 5;
        PyObject* dict = PyModule_GetDict(pyModule);
        if (!dict) {
            // TODO 获取错误
            return;
        }
        // 遍历python模块中的所有元素
        PyObject* keys = PyDict_Keys(dict);
        Py_ssize_t s = PyList_Size(keys);
        for (int i = 0; i < s; ++i) {
            PyObject* item = PyList_GetItem(keys, i);
            std::string attributeName(_PyUnicode_AsString(item));
            std::cout << attributeName << std::endl;
            if (attributeName.rfind("__", 0) == 0) {
                // __开头的忽略
            }
            else {
                // 获取模块中的参数。
                PyObject* paramter = PyDict_GetItemString(dict, attributeName.c_str());
                // 获取参数对象类型
                PyTypeObject* typeObject = paramter->ob_type;
                //std::cout << typeObject->tp_name << std::endl;
                if (strlen(PyActivity::paramterTypeName) == strlen(typeObject->tp_name) &&
                    (strncmp(PyActivity::paramterTypeName, typeObject->tp_name, strlen(PyActivity::paramterTypeName))) == 0) {
                    // 根据指定的参数类型判断是否在变量列表中
                    if (this->parameters.count(attributeName) == 0) {
                        // TODO 变量名不存在 报错
                        std::cout << "变量名不存在 报错" << std::endl;
                    }
                    else {
                        // 计算输入参数表达式的结果
                        Object* result = this->parameters[attributeName]->run(context);

                        // 创建对应类型的参数数据;
                        // 参数表达式的计算结果，输入到python模块中
                        PyObject* value = PyActivity::convertAstObjectToPyObject(result);
                        pyResult = PyObject_SetAttrString(paramter, "result", value);

                        //PyDict_SetItemString(dict, attributeName.c_str(), paramter);

                        // TODO 删除result;
                        // TODO delete result;
                    }
                }
                //std::cout << "------------" << std::endl;

                //Py_CLEAR(typeObject);
                //Py_CLEAR(paramter);
            }
            attributeName.clear();
            //Py_CLEAR(item);
            //std::cout << "------------" << std::endl;
        }
        //Py_CLEAR(keys);
        //Py_CLEAR(dict);


    }

    /// <summary>
    /// 函数的入参
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    PyObject* PyActivity::getFunctionParameters(workflow::ast::executors::Context* context) {
        // 
        size_t paramsCount(this->functionParameters.size());
        PyObject* pArgs = NULL;
        if (paramsCount > 0) {
            pArgs = PyTuple_New(paramsCount);
            for (int i = 0; i < paramsCount; i++) {
                Object* result = this->functionParameters[i]->run(context);
                // 变量添加到python参数列表中
                PyTuple_SetItem(pArgs, i, PyActivity::convertAstObjectToPyObject(result));
                delete result;
            }
        }
        return pArgs;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    PyObject* PyActivity::convertAstObjectToPyObject(workflow::ast::types::Object* value) {
        PyObject* result = NULL;
        if (value != nullptr) {
            if (value->getClassName() == workflow::framework::types::AstPyObject::className) {
                // 如果返回的是python对象。不转化。直接返回
                return  ((workflow::framework::types::AstPyObject*)value)->value;
            }
            else if (value->getClassName() == workflow::ast::types::Integer::className) {
                result = Py_BuildValue("i", ((workflow::ast::types::Integer*)value)->value);
            }
            // long
            else  if (value->getClassName() == workflow::ast::types::Long::className) {
                result = Py_BuildValue("l", ((workflow::ast::types::Long*)value)->value);
            }
            // str
            else if (value->getClassName() == workflow::ast::types::String::className) {
                result = Py_BuildValue("s", ((workflow::ast::types::String*)value)->value);
            }
            // float
            else if (value->getClassName() == workflow::ast::types::Float::className) {
                result = Py_BuildValue("d", ((workflow::ast::types::Float*)value)->value);
            }
            // null
            else if (value->getClassName() == workflow::ast::types::Null::className) {
                result = Py_BuildValue("z", NULL);
            }
            else {
                // TODO 没法处理的数据类型
                std::cout << "没法处理的数据类型" << std::endl;
            }
        }
        else
        {
            // TODO 传入的参数是null
            std::cout << "传入的参数是null" << std::endl;
        }
        return result;
    }
}