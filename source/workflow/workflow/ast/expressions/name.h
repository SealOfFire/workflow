#pragma once

#include "expression.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    /// <summary>
    /// 变量表达式
    /// </summary>
    class SHARED_LIB_API Name : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_NAME;

        /// <summary>
        /// 变量的标识
        /// </summary>
        string id;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="id"></param>
        Name(string id);

        virtual Object* execute(executors::Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(executors::Context* context);

        /// <summary>
        /// 表达式是否是变量。如果是变量，返回变量名字符串
        /// 不是变量返回null
        /// </summary>
        /// <returns></returns>
        virtual std::string isName();
    };
}