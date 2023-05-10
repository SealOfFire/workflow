#pragma once

#include "expression.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    /// <summary>
    /// 创建一个list数据对象
    /// </summary>
    class SHARED_LIB_API List : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_EXPR_LIST;

        List();

        void push_back(Expression* expression);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        virtual Object* execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);

    protected:
        /// <summary>
        /// 要添加到list中的表达式列表
        /// </summary>
        vector<Expression*> value;

    };

}