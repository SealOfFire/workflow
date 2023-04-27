#pragma once

#include <map>
#include <string>
#include <vector>
#include "statement.h"

using namespace std;
using namespace workflow::ast;

namespace workflow::ast::statements {

    /// <summary>
    /// 容器
    /// </summary>
    class SHARED_LIB_API Container : public Statement {
    public:
        static constexpr const char* className = CLASS_NAME_CONTAINER;

        /// <summary>
        /// 子组件列表
        /// </summary>
        vector<Statement*> children;

        Container();
        ~Container();

        /// <summary>
        /// 
        /// </summary>
        void execute(Context* context);

        virtual string getClassName() const;

        /// <summary>
        /// 像容器中添加语句
        /// </summary>
        /// <param name="statement"></param>
        void addStatement(Statement* statement);

        /// <summary>
        /// 转换成脚本
        /// </summary>
        /// <returns></returns>
        virtual string toScriptCode(Context* context);
    };
}