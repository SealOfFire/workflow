#pragma once

#include "expression.h"

namespace workflow::ast::expressions {

    class SHARED_LIB_API Dictionary : public Expression {
    public:
        static constexpr const char* className = CLASS_NAME_EXPR_DICT;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        void insert(Expression* key, Expression* value);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="context"></param>
        /// <returns></returns>
        virtual Object* execute(executors::Context* context);

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        virtual string getClassName() const;

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(executors::Context* context);

    protected:

        map<Expression*, Expression*> values;
        //vector<Expression*> keys;
        //vector<Expression*> values;

    };

}