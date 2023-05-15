#pragma once

#include "object.h"

using namespace std;

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API String : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_STRING;

        string value;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="value"></param>
        String(string value);
        ~String();

        virtual string getClassName() const;

        virtual string toString();

        static std::string stringToUTF8(const std::string str);
        static std::string UTF8ToString(const std::string str);
    };
}