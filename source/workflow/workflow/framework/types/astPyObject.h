#pragma once

#include <Python.h>
#include <types/object.h>
#include "types.h"

namespace workflow::framework::types {

    /// <summary>
    /// 
    /// </summary>
    class AstPyObject :public workflow::ast::types::Object {
    public:
        static constexpr const char* className = CLASS_NAME_PY_OBJECT;

        PyObject* value;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="value"></param>
        AstPyObject(PyObject* value);

        /// <summary>
        /// 
        /// </summary>
        ~AstPyObject();

        /// <summary>
        /// 获取类型名称
        /// </summary>
        /// <returns></returns>
        virtual string getClassName() const;

        static AstPyObject* create(PyObject* value);
    };

}