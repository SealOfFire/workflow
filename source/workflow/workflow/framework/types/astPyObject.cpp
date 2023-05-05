#include "astPyObject.h"

namespace workflow::framework::types {

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="value"></param>
    AstPyObject::AstPyObject(PyObject* value) :value(value) {
    }

    AstPyObject::~AstPyObject() {
        Py_DECREF(this->value);
        //Py_CLEAR(this->value);
    }

    std::string AstPyObject::getClassName() const {
        return  AstPyObject::className;
    }
}