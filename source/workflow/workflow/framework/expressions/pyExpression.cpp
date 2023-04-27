#include <Python.h>
#include "pyExpression.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::types;

namespace workflow::framework::expressions {

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

        // TODO 计算python脚本

        return nullptr;
    }

    std::string PyExpression::toScriptCode(Context* context) {
        return "PythonExpression(" + this->value + ")";
    }
}