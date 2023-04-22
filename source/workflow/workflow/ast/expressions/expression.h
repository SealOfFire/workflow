#pragma once

#include<string>
#include<iostream>
#include "expressions.h"
#include "../types/object.h"
#include "../executor/context.h"

using namespace std;
using namespace workflow::ast;
using namespace workflow::ast::executor;
using namespace workflow::ast::types;

/// <summary>
/// 
/// </summary>
namespace workflow::ast::expressions {

    /// <summary>
    /// 表达式
    /// </summary>
    class Expression {
    public:
        static constexpr const char* className = CLASS_NAME_EXPRESSION;

        /// <summary>
        /// 断点
        /// </summary>
        bool breakpoint = false;

        /// <summary>
        /// 
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
        /// 运行表达式
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
    };
}