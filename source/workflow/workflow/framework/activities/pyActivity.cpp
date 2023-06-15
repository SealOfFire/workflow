//#include <expressions/constant.h>
#include <expressions/name.h>
#include <expressions/subscript.h>
#include <expressions/value.h>
#include <modules/module.h>
#include <statements/assign.h>
#include <types/boolean.h>
#include <types/dictionary.h>
#include <types/float.h>
#include <types/integer.h>
#include <types/list.h>
#include <types/long.h>
#include <types/null.h>
#include <types/string.h>
#include "pyActivity.h"
#include "../pyTools.h"
#include "../executors/executor.h"
#include "../expressions/pyExpression.h"
#include "../types/astPyObject.h"


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
                        PyObject* value = convertAstObjectToPyObject(result);
                        // 回调函数 设置或者读取属性
                        //(this->*callback)(attributeName.c_str(), value);
                        // Py_CLEAR(value);
                        pyResult = PyObject_SetAttrString(this->pyModule, attributeName.c_str(), value); // TODO 或者get
                        if (pyResult < 0) {
                            // TODO 设置值出错
                            std::cout << "设置值到python中出错" << std::endl;
                        }

                        // 删除result; TODO 这里可能有内存泄露
                        // Object::release(result);
                        // 
                        Py_DECREF(value);
                        //Py_CLEAR(value);
                    }
                    else {
                        // python->ast
                        // 这里的属性值如果是个变量名。需要python脚本中的值修改组件属性值。把值从python脚本中传出到ast中
                        if (this->properties[attributeName]->getClassName() == ast::expressions::Name::className) {
                            ast::expressions::Name* name = (ast::expressions::Name*)this->properties[attributeName];

                            // 取出python中的值
                            PyObject* value = PyDict_GetItemString(this->dict, attributeName.c_str());

                            // 通过赋值语句设置变量
                            ast::expressions::Name target(name->id);
                            ast::expressions::Value expr(convertPyObjectToAstObject(value));
                            ast::statements::Assign assign(&target, &expr);
                            assign.run(context);
 
                            // 释放python
                            if (value != NULL && !PyList_Check(value) && !PyDict_Check(value)) {
                                Py_DECREF(value);
                            }
                        }
                        else if (this->properties[attributeName]->getClassName() == ast::expressions::Subscript::className) {
                            ast::expressions::Subscript* subscript = (ast::expressions::Subscript*)this->properties[attributeName];

                            // 取出python中的值
                            PyObject* value = PyDict_GetItemString(this->dict, attributeName.c_str());
                            //context->currentModule->variables[propertyName] = convertPyObjectToAstObject(value);

                            // 通过赋值语句设置变量
                            ast::expressions::Value expr(convertPyObjectToAstObject(value));
                            ast::statements::Assign assign(subscript, &expr);
                            assign.run(context);
                            
                            // 释放python
                            if (value != NULL && !PyList_Check(value) && !PyDict_Check(value)) {
                                Py_DECREF(value);
                            }
                        }
                        else if (this->properties[attributeName]->getClassName() == framework::expressions::PyExpression::className) {
                            framework::expressions::PyExpression* pyExpression = (framework::expressions::PyExpression*)this->properties[attributeName];
                            // 判断是变量，还是下标

                            framework::executors::Executor* executor = (framework::executors::Executor*)context->executor;
                            PyObject* args = PyTuple_New(2);
                            PyTuple_SetItem(args, 0, PyUnicode_FromString(pyExpression->value.c_str()));
                            ast::Variables* variables = context->currentModule->getVariables();
                            PyObject* local = convertAstVariablesToPyDict(variables);
                            PyTuple_SetItem(args, 1, local); // 局部变量列表

                            PyObject* result = PyEval_CallObject(executor->functionTestExpression, args);
                            PyObject* p1 = PyTuple_GetItem(result, 0);
                            PyObject* p2 = PyTuple_GetItem(result, 1);
                            PyObject* p3 = PyTuple_GetItem(result, 2);
                            PyObject* p4 = PyTuple_GetItem(result, 3);

                            ast::types::Boolean* v1 = (ast::types::Boolean*)convertPyObjectToAstObject(p1); // true是变量名
                            ast::types::Integer* v2 = (ast::types::Integer*)convertPyObjectToAstObject(p2); // 0变量名，1下标
                            ast::types::String* v3 = (ast::types::String*)convertPyObjectToAstObject(p3); // 变量名
                            // dict的话v4是string。list的话v4是string
                            ast::types::Object* v4 = convertPyObjectToAstObject(p4); // 下标
                            //ast::types::Integer* v4 = (ast::types::Integer*)convertPyObjectToAstObject(p4);

                            //Py_DECREF(local);

                            if (v1->value) {
                                // 取出python中的值
                                PyObject* value = PyDict_GetItemString(this->dict, attributeName.c_str());
                                switch (v2->value)
                                {
                                case 0: {
                                    // 变量
                                    ast::expressions::Name target(v3->value);
                                    ast::expressions::Value expr(convertPyObjectToAstObject(value));
                                    ast::statements::Assign assign(&target, &expr);
                                    assign.run(context);
                                    break;
                                }
                                case 1: {
                                    // 下标
                                    ast::expressions::Name target(v3->value);
                                    ast::types::Object* slice;
                                    if (v4->getClassName() == ast::types::Integer::className) {
                                        slice = ast::types::Integer::create(((ast::types::Integer*)v4)->value);
                                    }
                                    else if (v4->getClassName() == ast::types::String::className) {
                                        slice = ast::types::String::create(((ast::types::String*)v4)->value);
                                    }
                                    else {
                                        // TODO 下标数据类型错误
                                    }
                                    //ast::expressions::Constant constant(v4->value);
                                    ast::expressions::Value sliceValue(slice);
                                    ast::expressions::Subscript subscript(&target, &sliceValue);
                                    ast::expressions::Value expr(convertPyObjectToAstObject(value));
                                    ast::statements::Assign assign(&subscript, &expr);
                                    assign.run(context);
                                    Object::release(slice);
                                    break;
                                }
                                default:
                                    // TODO 未处理的数据类型
                                    break;
                                }
                                // 变量
                                //if (v2->value == 0) {
                                //    // 变量
                                //    // 通过赋值语句设置变量
                                //    ast::expressions::Name target(v3->value);
                                //    ast::expressions::Value expr(convertPyObjectToAstObject(value));
                                //    ast::statements::Assign assign(&target, &expr);
                                //    assign.run(context);

                                //}
                                //else if (v2->value == 1) {
                                //    // 下标

                                //}
                                //else {
                                //    // TODO 未处理的数据类型
                                //}

                                //if (value != NULL && !PyList_Check(value) && !PyDict_Check(value)) {
                                //    Py_DECREF(value);
                                //}
                            }

                            ast::types::Object::release(v1);
                            ast::types::Object::release(v2);
                            ast::types::Object::release(v3);
                            ast::types::Object::release(v4);
                        }
                        else {
                            // 其他的不处理
                        }
     

                        //std::string propertyName = this->properties[attributeName]->isName();
                        //if (propertyName.size() != 0) {
                        //    // 表达式是个变量名。可以传出数值
                        //    PyObject* value = PyDict_GetItemString(this->dict, attributeName.c_str()); // TODO 或者get
                        //    if (!value) {
                        //        // TODO 设置值出错
                        //        std::cout << "从python获取值出错" << std::endl;
                        //    }
                        //    // TODO 字典和list时候的处理没有 
                        //    // TODO 赋值前删掉旧值避免泄露。检查其他的地方map是否会泄露
                        //    context->currentModule->variables[propertyName] = convertPyObjectToAstObject(value);
                        //    // 返回数据中如果有list。这里调用Py_DECREF会报错
                        //    //bool is = PyDict_Check(value);
                        //    if (value != NULL && !PyList_Check(value) && !PyDict_Check(value)) {
                        //        Py_DECREF(value);
                        //    }
                        //}
                        //propertyName.clear();
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
                PyTuple_SetItem(pArgs, i, convertAstObjectToPyObject(result));
                //delete result;
                Object::release(result);
            }
        }
        return pArgs;
    }

}