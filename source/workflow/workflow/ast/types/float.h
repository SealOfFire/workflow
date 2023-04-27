#pragma once
#include "object.h"

using namespace std;
using namespace workflow::ast;

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API Float : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_FLOAT;

        float value;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="value"></param>
        Float(float value);

        virtual string getClassName() const;

        virtual string toString();
    };
}