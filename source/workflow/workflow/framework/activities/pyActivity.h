#pragma once
#include <stdio.h>
#include <Python.h>
#include <string>
#include "activities.h"
#include "activity.h"

namespace workflow::framework::activities {

    /// <summary>
    /// python脚本构成的语句
    /// </summary>
    class SHARED_LIB_API PyActivity : public Activity {
    public:

        /// <summary>
        /// python模块名
        /// </summary>
        std::string moduleName;

        /// <summary>
        /// 函数名
        /// </summary>
        std::string functionName;

        /// <summary>
        /// 函数的入参列表
        /// 按顺序传入
        /// </summary>
        vector<Expression*> functionParameters;

        /// <summary>
        /// 函数的返回值
        /// TODO 没有释放
        /// </summary>
        PyObject* functionReturn = nullptr;

        /// <summary>
        /// 创建一个调用python模块的组件
        /// </summary>
        /// <param name="moduleName">模块名称</param>
        /// <param name="functionName">调用的函数名称</param>
        PyActivity(std::string moduleName, std::string functionName);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="env"></param>
        void executeActivity(workflow::ast::executors::Context* context);

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual std::string toScriptCode(Context* context);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        static PyObject* convertAstObjectToPyObject(workflow::ast::types::Object* value);

        /// <summary>
        /// 
        /// </summary>
        static workflow::ast::types::Object* convertPyObjectToAstObject(PyObject* value);

    private:

        //typedef void (PyActivity::* changePropertiesFunction)(const char*, PyObject*);

        /// <summary>
        /// 加载的python脚本模块
        /// </summary>
        PyObject* pyModule = nullptr;

        PyObject* dict = nullptr;

        /// <summary>
        /// 遍历属性
        /// </summary>
        /// <param name="context"></param>
        void iterateProperties(workflow::ast::executors::Context* context, bool set);

        /// <summary>
        /// 调用函数的入参
        /// </summary>
        /// <param name="context"></param>
        /// <param name=""></param>
        /// <returns></returns>
        PyObject* getFunctionParameters(workflow::ast::executors::Context* context);

    };
}
