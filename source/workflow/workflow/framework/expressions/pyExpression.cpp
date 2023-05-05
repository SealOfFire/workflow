#include <regex>
#include <Python.h>
#include <modules/module.h>
#include "pyExpression.h"
#include "../activities/pyActivity.h"
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

        int pyResult = -1;

        // 计算python脚本
        PyObject* code = Py_CompileString(this->value.c_str(), "<string>", Py_eval_input);
        PyObject* global_dict = PyDict_New();

        PyObject* local_dict = PyDict_New(); // TODO 需要把模块的变量列表全部转成python变量
        for (auto [name, value] : context->currentModule->variables) {
            PyObject* object = workflow::framework::activities::PyActivity::convertAstObjectToPyObject(value);
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
        PyObject* result = PyEval_EvalCode(code, global_dict, local_dict);

        //PyTypeObject* typeObject = result->ob_type;
        //std::cout << typeObject->tp_name << std::endl;

        // TODO resultValue需要delete
        AstPyObject* returnValue = new AstPyObject(result);

        /*
        int nResult;
        int pyResult = PyArg_Parse(result, "i", &nResult);
        if (pyResult < 0) {
            // TODO 表达式计算出错
            std::cout << "表达式计算出错" << std::endl;
        }
        */

        Py_DECREF(global_dict);
        Py_DECREF(code);

        return returnValue;
    }

    std::string PyExpression::toScriptCode(Context* context) {
        return "PythonExpression(" + this->value + ")";
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string PyExpression::getClassName() const {
        return PyExpression::className;
    }

    std::string PyExpression::isName() {
        // 判读当前的python表达式是否是一个变量
        // 正则表达式匹配。匹配中括号结尾的时候，获取中括号内的参数
        // TODO list和dict不支持

        std::regex regexName(REGULAR_NAME);
        if (std::regex_match(this->value, regexName)) {
            return this->value;
        }
        return Expression::isName();
    }
}