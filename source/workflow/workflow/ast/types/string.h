#pragma once

#include "object.h"

using namespace std;

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    class String : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_STRING;

        std::string value;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="value"></param>
        String(string value);

        virtual string getClassName() const;

        virtual string toString();
    };
}