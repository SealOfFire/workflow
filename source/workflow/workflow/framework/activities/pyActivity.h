#pragma once

#include <string>
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

        // TODO 参数列表

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
    };
}
