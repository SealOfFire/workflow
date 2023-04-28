#include <Python.h>
#include "pyExpression.h"
#include "../types/astPyObject.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::types;
using namespace workflow::framework::types;

namespace workflow::framework::expressions {

    PyExpression::PyExpression(std::string value) :value(value) {

    }

    /// <summary>
    /// 计算表达式
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* PyExpression::execute(Context* context) {

        //
        if (!Py_IsInitialized()) {
            // TODO 最后改成异常
            std::cout << "python 初始化出错" << std::endl;
            return nullptr;
        }

        // 计算python脚本
        PyObject* code = Py_CompileString(this->value.c_str(), "<string>", Py_eval_input);
        PyObject* global_dict = PyDict_New();
        PyObject* local_dict = PyDict_New(); // TODO 需要把模块的变量列表全部转成python变量
        PyObject* result = PyEval_EvalCode(code, global_dict, local_dict);

        PyTypeObject* typeObject = result->ob_type;
        //std::cout << typeObject->tp_name << std::endl;

        AstPyObject object(result);
        /*
        int nResult;
        int pyResult = PyArg_Parse(result, "i", &nResult);
        if (pyResult < 0) {
            // TODO 表达式计算出错
            std::cout << "表达式计算出错" << std::endl;
        }
        */

        return &object;
    }

    std::string PyExpression::toScriptCode(Context* context) {
        return "PythonExpression(" + this->value + ")";
    }

}