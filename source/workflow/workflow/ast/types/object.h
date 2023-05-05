#pragma once

#include <string>
#include "types.h"
#include "../../exportLib.h"

using namespace std;

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API Object {
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

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        int getReferenceCount();

        /// <summary>
        /// 增加引用计数
        /// </summary>
        void increaseReferenceCount();

        /// <summary>
        /// 减少引用计数
        /// </summary>
        void decreaseReferenceCount();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="object"></param>
        static void release(Object* object);

    private:

        /// <summary>
        /// 引用计数
        /// </summary>
        int referenceCount = 0;

    };
}
