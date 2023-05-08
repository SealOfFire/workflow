#include <expressions/name.h>
#include <modules/module.h>
#include <types/boolean.h>
#include <types/dictionary.h>
#include <types/float.h>
#include <types/integer.h>
#include <types/list.h>
#include <types/long.h>
#include <types/null.h>
#include <types/string.h>
#include "../types/astPyObject.h"
#include "pyActivity.h"
#include "../expressions/pyExpression.h"

namespace workflow::framework::activities {

    PyActivity::PyActivity(std::string moduleName, std::string functionName) :moduleName(moduleName), functionName(functionName) {
        this->pyModule = nullptr;
        this->dict = nullptr;
    }

    /// <summary>
    /// 运行语句
    /// </summary>
    /// <param name="context"></param>
    void PyActivity::executeActivity(workflow::ast::executors::Context* context) {

        //
        if (!Py_IsInitialized()) {
            // TODO 最后改成异常
            PyErr_Print();
            std::cout << "python 初始化出错" << std::endl;
            return;
        }

        // 根据模块名导入模块
        // 调用python文件名，不需要写后缀
        this->pyModule = PyImport_ImportModule(this->moduleName.c_str());
        if (!this->pyModule) {
            PyErr_Print();
            std::cout << "没找到模块1" << this->moduleName << std::endl;
            return;
        }

        this->dict = PyModule_GetDict(this->pyModule);
        if (!this->dict) {
            PyErr_Print();
            std::cout << "没找到模块2" << this->moduleName << std::endl;
            return;
        }

        // 计算模块的输入参数
        // 设置模块的全局参数
        this->iterateProperties(context, true);

        // 函数的入参
        PyObject* pArgs = this->getFunctionParameters(context);

        // 调用的函数名
        PyObject* pFunc = PyObject_GetAttrString(this->pyModule, this->functionName.c_str());
        if (!pFunc || !PyCallable_Check(pFunc)) {
            PyErr_Print();
            std::cout << "没找到函数" << this->functionName.c_str() << std::endl;
            return;
        }

        // 调用模块中的运行函数
        //PyObject_CallObject(pFunc, pArgs);
        this->functionReturn = PyEval_CallObject(pFunc, pArgs); // 带返回值的函数调用

        // 计算模块的输出参数
        this->iterateProperties(context, false);

        // 释放资源
        if (this->functionReturn != nullptr) {
            Py_DECREF(this->functionReturn);
            //Py_CLEAR(this->functionReturn);
        }

        if (this->functionParameters.size() > 0) {
            Py_DECREF(pArgs);
            //Py_CLEAR(pArgs);
        }

        // 这里释放资源会在Py_Finalize时报错
        //Py_DECREF(pFunc);
        //Py_CLEAR(pFunc);
        //Py_DECREF(this->dict);
        //Py_CLEAR(this->dict);

        //Py_DECREF(this->pyModule);
        //Py_CLEAR(this->pyModule);

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
        for (auto [name, expr] : this->properties) {
            output += indent2 + name + " = " + expr->toScriptCode(context) + context->newline;
        }

        output += indent + "}" + context->newline;
        context->indentLevel--;

        return output;
    }

    /// <summary>
    /// 遍历属性
    /// </summary>
    /// <param name="context"></param>
    void PyActivity::iterateProperties(workflow::ast::executors::Context* context, bool set) {
        // 从模块中获取模块的所有元素
        //PyObject* dict = PyModule_GetDict(this->pyModule);
        // python执行结果
        int pyResult = -1;

        // 遍历python模块中的所有元素
        PyObject* keys = PyDict_Keys(this->dict);
        Py_ssize_t s = PyList_Size(keys);
        for (int i = 0; i < s; ++i) {
            // 模块的所有属性
            PyObject* item = PyList_GetItem(keys, i);

            // python对象类型转成c++数据类型字符串
            std::string attributeName(_PyUnicode_AsString(item));
            //std::cout << attributeName << std::endl;

            if (attributeName.rfind("__", 0) == 0) {
                // __开头的忽略
            }
            else {
                // 获取模块中的参数。
                //PyObject* paramter = PyDict_GetItemString(dict, attributeName.c_str());

                if (this->properties.count(attributeName) == 0) {
                    // python模块中的局域变量，不是要传入的属性
                    // std::cout << "python模块中的局域变量，不是要传入的属性" << std::endl;
                }
                else {
                    if (set) {
                        // ast->python
                        // 属性传入到python脚本中
                        // 计算输入参数表达式的结果
                        Object* result = this->properties[attributeName]->run(context); // python传出到局部变量的时候，不需要计算值
                        // 创建对应类型的参数数据;
                        // 参数表达式的计算结果，输入到python模块中
                        PyObject* value = PyActivity::convertAstObjectToPyObject(result);
                        // 回调函数 设置或者读取属性
                        //(this->*callback)(attributeName.c_str(), value);
                        // Py_CLEAR(value);
                        pyResult = PyObject_SetAttrString(this->pyModule, attributeName.c_str(), value); // TODO 或者get
                        if (pyResult < 0) {
                            // TODO 设置值出错
                            std::cout << "设置值到python中出错" << std::endl;
                        }

                        // 删除result;
                        Object::release(result);
                        // 
                        Py_DECREF(value);
                        //Py_CLEAR(value);
                    }
                    else {
                        // python->ast
                        // 这里的属性值如果是个变量名。需要python脚本中的值修改组件属性值。把值从python脚本中传出到ast中
                        std::string propertyName = this->properties[attributeName]->isName();
                        if (propertyName.size() != 0) {
                            // 表达式是个变量名。可以传出数值
                            PyObject* value = PyDict_GetItemString(this->dict, attributeName.c_str()); // TODO 或者get
                            if (!value) {
                                // TODO 设置值出错
                                std::cout << "从python获取值出错" << std::endl;
                            }
                            // TODO 字典和list时候的处理没有 
                            // TODO 赋值前删掉旧值避免泄露。检查其他的地方map是否会泄露
                            context->currentModule->variables[propertyName] = this->convertPyObjectToAstObject(value);
                            // 返回数据中如果有list。这里调用Py_DECREF会报错
                            if (!PyList_Check(value)) {
                                Py_DECREF(value);
                            }
                        }
                        propertyName.clear();
                    }
                }
            }

            attributeName.clear();
            // TODO 这里释放资源会在Py_Finalize时报错
            //Py_CLEAR(item);
            //Py_DECREF(item);
        }
        // 释放资源
        Py_DECREF(keys);
        //Py_CLEAR(keys);
    }

    ///// <summary>
    ///// 
    ///// </summary>
    ///// <param name="context"></param>
    //void PyActivity::setProperties(const char* attributeName, PyObject* value) {
    //    int pyResult = -1;
    //    pyResult = PyObject_SetAttrString(this->pyModule, attributeName, value); // TODO 或者get
    //    if (pyResult < 0) {
    //        // TODO 设置值出错
    //        std::cout << "设置值到python中出错" << std::endl;
    //    }
    //}

    ///// <summary>
    ///// 
    ///// </summary>
    ///// <param name="attributeName"></param>
    ///// <param name="value">不需要</param>
    //PyObject* PyActivity::getProperties(const char* attributeName) {
    //    int pyResult = -1;
    //    PyObject* dict = PyModule_GetDict(this->pyModule);
    //    PyObject* value = PyDict_GetItemString(dict, attributeName); // TODO 或者get
    //    if (!value) {
    //        // TODO 设置值出错
    //        std::cout << "从python获取值出错" << std::endl;
    //    }
    //    // TODO 值转换成ast对象。保存到局部变量中
    //    // TODO
    //    // Py_CLEAR(value);
    //    // TODO 字典和list时候的处理没有
    //    return value;
    //}

    ///// <summary>
    ///// 设置组件的参数
    ///// </summary>
    //void PyActivity::setParameters(workflow::ast::executors::Context* context) {
    //    //PyImport_GetModuleDict
    //    // 从模块中获取模块的所有元素
    //    int pyResult = 5;
    //    PyObject* dict = PyModule_GetDict(this->pyModule);
    //    if (!dict) {
    //        // TODO 获取错误
    //        return;
    //    }
    //    // 遍历python模块中的所有元素
    //    PyObject* keys = PyDict_Keys(dict);
    //    Py_ssize_t s = PyList_Size(keys);
    //    for (int i = 0; i < s; ++i) {
    //        PyObject* item = PyList_GetItem(keys, i);
    //        std::string attributeName(_PyUnicode_AsString(item));
    //        //std::cout << attributeName << std::endl;
    //        if (attributeName.rfind("__", 0) == 0) {
    //            // __开头的忽略
    //        }
    //        else {
    //            // 获取模块中的参数。
    //            PyObject* paramter = PyDict_GetItemString(dict, attributeName.c_str());
    //            // 获取参数对象类型
    //            PyTypeObject* typeObject = paramter->ob_type;
    //            //std::cout << typeObject->tp_name << std::endl;
    //            if (strlen(PyActivity::paramterTypeName) == strlen(typeObject->tp_name) &&
    //                (strncmp(PyActivity::paramterTypeName, typeObject->tp_name, strlen(PyActivity::paramterTypeName))) == 0) {
    //                // 根据指定的参数类型判断是否在变量列表中
    //                if (this->properties.count(attributeName) == 0) {
    //                    // TODO 变量名不存在 报错
    //                    std::cout << "变量名不存在 报错" << std::endl;
    //                }
    //                else {
    //                    // 计算输入参数表达式的结果
    //                    Object* result = this->properties[attributeName]->run(context);

    //                    // 创建对应类型的参数数据;
    //                    // 参数表达式的计算结果，输入到python模块中
    //                    PyObject* value = PyActivity::convertAstObjectToPyObject(result);
    //                    // TODO 如果PyObject是个变量名,这里记录下来用于计算结束后，变脸结果回传给组件外部

    //                    //pyResult = PyObject_SetAttrString(paramter, "value", this->parameters[attributeName]->toScriptCode(context));
    //                    pyResult = PyObject_SetAttrString(paramter, "result", value); // TODO 或者get
    //                    if (pyResult < 0) {
    //                        // TODO 设置值出错
    //                        std::cout << "设置值出错" << std::endl;
    //                    }
    //                    //PyDict_SetItemString(dict, attributeName.c_str(), paramter);

    //                    // TODO 删除result;
    //                    // TODO delete result;
    //                }
    //            }
    //            //std::cout << "------------" << std::endl;

    //            //Py_CLEAR(typeObject);
    //            //Py_CLEAR(paramter);
    //        }
    //        attributeName.clear();
    //        //Py_CLEAR(item);
    //        //std::cout << "------------" << std::endl;
    //    }
    //    //Py_CLEAR(keys);
    //    //Py_CLEAR(dict);


    //}

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
                //delete result;
                Object::release(result);
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
                result = Py_BuildValue("s", ((workflow::ast::types::String*)value)->value.c_str());
                //result = Py_BuildValue("s", "中文"); // TODO 中文需要转成utf8
            }
            // float
            else if (value->getClassName() == workflow::ast::types::Float::className) {
                result = Py_BuildValue("d", ((workflow::ast::types::Float*)value)->value);
            }
            // null
            else if (value->getClassName() == workflow::ast::types::Null::className) {
                result = Py_BuildValue("z", NULL);
            }
            else if (value->getClassName() == workflow::ast::types::List::className) {
                // TODO 递归
            }
            else if (value->getClassName() == workflow::ast::types::Dictionary::className) {
                // TODO 递归
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

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    Object* PyActivity::convertPyObjectToAstObject(PyObject* value) {
        // TODO
        if (strlen(value->ob_type->tp_name) == strlen(PY_TYPE_STRING) &&
            (strncmp(value->ob_type->tp_name, PY_TYPE_STRING, strlen(PY_TYPE_STRING))) == 0) {
            // 字符串类型
            Py_ssize_t size;
            const char* ptr = PyUnicode_AsUTF8AndSize(value, &size);
            std::string str(ptr, size);
            return new ast::types::String(str);
        }
        else if (strlen(value->ob_type->tp_name) == strlen(PY_TYPE_INTEGER) &&
            (strncmp(value->ob_type->tp_name, PY_TYPE_INTEGER, strlen(PY_TYPE_INTEGER))) == 0) {
            // integer
            return new ast::types::Integer(_PyLong_AsInt(value));
        }
        else if (strlen(value->ob_type->tp_name) == strlen(PY_TYPE_FLOAT) &&
            (strncmp(value->ob_type->tp_name, PY_TYPE_FLOAT, strlen(PY_TYPE_FLOAT))) == 0) {
            // float
            return new ast::types::Float(PyFloat_AsDouble(value));
        }
        else if (strlen(value->ob_type->tp_name) == strlen(PY_TYPE_NONE) &&
            (strncmp(value->ob_type->tp_name, PY_TYPE_NONE, strlen(PY_TYPE_NONE))) == 0) {
            // none
            //return new ast::types::List();
            return new ast::types::Null();
        }
        else if (strlen(value->ob_type->tp_name) == strlen(PY_TYPE_DICTIONARY) &&
            (strncmp(value->ob_type->tp_name, PY_TYPE_DICTIONARY, strlen(PY_TYPE_DICTIONARY))) == 0) {
            // dict
            // TODO 递归
            int a = 0;
            a++;
        }
        else if (strlen(value->ob_type->tp_name) == strlen(PY_TYPE_LIST) &&
            (strncmp(value->ob_type->tp_name, PY_TYPE_LIST, strlen(PY_TYPE_LIST))) == 0) {
            // list
            ast::types::List* result = new ast::types::List();
            for (int i = 0; i < PyList_Size(value); i++) {
                PyObject* listVal = PyList_GetItem(value, i);
                //PyObject* listVal = PySequence_GetItem(value, i);
                result->value.push_back(PyActivity::convertPyObjectToAstObject(listVal));
                //Py_DECREF(listVal);
                //Py_CLEAR(listVal);
            }
            return result;
        }
        else if (strlen(value->ob_type->tp_name) == strlen(PY_TYPE_BOOLEAN) &&
            (strncmp(value->ob_type->tp_name, PY_TYPE_BOOLEAN, strlen(PY_TYPE_BOOLEAN))) == 0) {
            // bool
            return new ast::types::Boolean(PyBool_Check(value));
        }
        else if (strlen(value->ob_type->tp_name) == strlen(PY_TYPE_TUPLE) &&
            (strncmp(value->ob_type->tp_name, PY_TYPE_TUPLE, strlen(PY_TYPE_TUPLE))) == 0) {
            // tuple
            // TODO
        }
        else {
            // 其他的python数据类型。直接保存为python数据
            return new framework::types::AstPyObject(value);
        }

        return new ast::types::Object();
    }

}