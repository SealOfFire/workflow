#pragma once
#include <Python.h>
#include <executors/context.h>

namespace workflow::framework::executors {

    /// <summary>
    /// 
    /// </summary>
    class Context : public workflow::ast::executors::Context {
    public:
        PyObject* moduleTestExpression;
        PyObject* functionTestExpression;
    };
}