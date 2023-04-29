#pragma once

#include <string>
#include <executors/context.h>
#include <expressions/expression.h>
#include <statements/statement.h>
#include "../../exportLib.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;

namespace workflow::framework::activities {

    /// <summary>
    /// 组件基类
    /// TODO 继承 语句，还是模块
    /// </summary>
    class SHARED_LIB_API Activity :public Statement {
    public:
        // TODO 执行前延迟
        // TODO 执行后延迟
        // TODO 错误执行

        const char* paramterTypeName = "Parameter";

        /// <summary>
        /// 组件的属性列表
        /// </summary>
        std::map<std::string, Expression*> properties;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="env"></param>
        void execute(Context* context);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        virtual void executeActivity(Context* context);

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual std::string toScriptCode(Context* context);
    };
}