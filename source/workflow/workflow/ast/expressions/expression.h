#pragma once

#include <iostream>
#include <string>
#include "../common.h"
#include "expressions.h"
#include "../executors/context.h"
#include "../types/object.h"
#include "../../exportLib.h"

using namespace std;
using namespace workflow::ast;
using namespace workflow::ast::executors;
using namespace workflow::ast::types;

/// <summary>
/// 
/// </summary>
namespace workflow::ast::expressions {

    /// <summary>
    /// 表达式
    /// </summary>
    class SHARED_LIB_API Expression {
    public:
        static constexpr const char* className = CLASS_NAME_EXPRESSION;

        /// <summary>
        /// 断点
        /// </summary>
        bool breakpoint = false;

        /// <summary>
        /// 执行脚本
        /// </summary>
        /// <param name="env"></param>
        Object* run(Context* context);

        /// <summary>
        /// 注释
        /// </summary>
        //string comment;

        /// <summary>
        /// 表达式值
        /// </summary>
        //string value;

        /// <summary>
        /// 表达式结果的值类型
        /// </summary>
        //ValueType valueType;

        /// <summary>
        /// 每个脚本子类自己实现执行脚本时的功能
        /// </summary>
        /// <returns>返回指向结果的指针</returns>
        virtual Object* execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// debug模式运行时的处理
        /// </summary>
        virtual void debugProcess(Context* context);

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);

        /// <summary>
        /// 表达式是否是变量。如果是变量，返回变量名字符串
        /// 不是变量返回null
        /// </summary>
        /// <returns></returns>
        virtual std::string isName();
    };
}