#include "pyTools.h"
#include <types/boolean.h>
#include <types/dictionary.h>
#include <types/float.h>
#include <types/integer.h>
#include <types/list.h>
#include <types/long.h>
#include <types/null.h>
#include <types/string.h>
#include "./types/astPyObject.h"

namespace workflow::framework {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    PyObject* convertAstObjectToPyObject(workflow::ast::types::Object* value) {
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
                workflow::ast::types::List* list = (workflow::ast::types::List*)value;
                PyObject* pyList = PyList_New(list->count());
                for (int i = 0; i < list->count(); i++) {
                    PyList_SetItem(pyList, i, convertAstObjectToPyObject(list->elementAt(i)));
                    //PyList_Append(pyList, convertAstObjectToPyObject(list->value[i]));
                }
                return pyList;
            }
            else if (value->getClassName() == workflow::ast::types::Dictionary::className) {
                workflow::ast::types::Dictionary* dict = (workflow::ast::types::Dictionary*)value;
                PyObject* pyDict = PyDict_New();
                for (auto [key, val] : dict->value) {
                    PyDict_SetItem(pyDict, PyUnicode_FromString(key.c_str()), convertAstObjectToPyObject(val));
                }
                return pyDict;
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
    workflow::ast::types::Object* convertPyObjectToAstObject(PyObject* value) {

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
            ast::types::Dictionary* result = new ast::types::Dictionary();
            PyObject* keys = PyDict_Keys(value);
            Py_ssize_t s = PyList_Size(keys);
            for (int i = 0; i < s; ++i) {
                // 模块的所有属性
                PyObject* item = PyList_GetItem(keys, i);

                // python对象类型转成c++数据类型字符串
                std::string key(_PyUnicode_AsString(item));

                PyObject* val = PyDict_GetItemString(value, key.c_str());
                result->value[key] = convertPyObjectToAstObject(val);
            }
            return result;
        }
        else if (strlen(value->ob_type->tp_name) == strlen(PY_TYPE_LIST) &&
            (strncmp(value->ob_type->tp_name, PY_TYPE_LIST, strlen(PY_TYPE_LIST))) == 0) {
            // list
            ast::types::List* result = new ast::types::List();
            for (int i = 0; i < PyList_Size(value); i++) {
                PyObject* listVal = PyList_GetItem(value, i);
                //PyObject* listVal = PySequence_GetItem(value, i);
                //result->value.push_back(convertPyObjectToAstObject(listVal));
                result->append(convertPyObjectToAstObject(listVal));
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

    /// <summary>
    /// 
    /// </summary>
    /// <param name="variables"></param>
    /// <returns></returns>
    PyObject* convertAstVariablesToPyDict(std::map<std::string, ast::types::Object*> variables) {

        int pyResult = -1;
        PyObject* local_dict = PyDict_New(); // TODO 需要把模块的变量列表全部转成python变量
        for (auto [name, value] : variables) {
            PyObject* object = convertAstObjectToPyObject(value);
            PyObject* key = Py_BuildValue("s", name.c_str());
            pyResult = PyDict_SetItem(local_dict, key, object);
            if (pyResult < 0) {
                // TODO 添加局域变量出错
                std::cout << "添加局域变量出错" << std::endl;
            }

            Py_DECREF(key);
            Py_DECREF(object);

            //Py_CLEAR(key);
            //Py_CLEAR(object);
        }
        return local_dict;
    }

    /// <summary>
    /// 
    /// </summary>
    PyObject* createTestExpressionModule() {

        PyObject* code = Py_CompileString(SOURCE1, "<string>", Py_file_input); // Py_file_input Py_eval_input

        //PyObject* local = PyDict_New();
        //PyDict_SetItem(local, PyUnicode_FromString("value"), PyUnicode_FromString("aaa[3+5]"));
        //PyObject* result = PyEval_EvalCode(module, PyDict_New(), local);

        PyObject* module = PyImport_ExecCodeModule("__test__", code);

        /*
        PyObject* func = PyObject_GetAttrString(module, "test");
        if (!func || !PyCallable_Check(func)) {
            // TODO 函数错误
            PyErr_Print();
            std::cout << "函数错误" << std::endl;
        }

        PyObject* args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyUnicode_FromString("aaa[3+5]"));

        PyObject* result = PyEval_CallObject(func, args);
        PyObject* p1 = PyTuple_GetItem(result, 0);
        PyObject* p2 = PyTuple_GetItem(result, 1);
        PyObject* p3 = PyTuple_GetItem(result, 2);

        ast::types::Object* v1 = convertPyObjectToAstObject(p1);
        ast::types::Object* v2 = convertPyObjectToAstObject(p2);
        ast::types::Object* v3 = convertPyObjectToAstObject(p3);
        */
        return module;

    }

}