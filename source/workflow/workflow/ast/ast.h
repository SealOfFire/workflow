#pragma once
#include <vector>
#include "./types/boolean.h"
#include "./types/object.h"
#include "./types/void.h"

namespace workflow::ast {

    class Manager {

    public:

        static types::Boolean* createBoolean(bool value);

        /// <summary>
        /// 创建一个object类型对象
        /// </summary>
        static types::Object* createObject();

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        static types::Void* createVoid();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="value"></param>
        static void deleteObject(types::Object* value);

    protected:
        static std::vector<types::Object*> variables;

    };

}