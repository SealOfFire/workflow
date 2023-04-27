#pragma once

#include <string>
#include "types.h"

using namespace std;

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    class Object {
    public:
        static constexpr const char* className = CLASS_NAME_OBJECT;

        //void* value;

        /// <summary>
        /// 构造函数
        /// </summary>
        /// <param name="value"></param>
        /// <param name="valueType"></param>
        //Object(void* value);

        //Object operator+(Object &value);
        virtual Object* Add(Object* value);
        virtual Object Add(Object& value);

        /// <summary>
        /// 获取类型名称
        /// </summary>
        /// <returns></returns>
        virtual string getClassName() const;

        /// <summary>
        /// 打印
        /// </summary>
        /// <returns></returns>
        virtual string toString();
    };
}
