#pragma once
#include <vector>
#include "./types/boolean.h"
#include "./types/dictionary.h"
#include "./types/float.h"
#include "./types/integer.h"
#include "./types/list.h"
#include "./types/long.h"
#include "./types/null.h"
#include "./types/object.h"
#include "./types/string.h"
#include "./types/void.h"

namespace workflow::ast {

    //namespace expressions {
    //    class Constant;
    //}

    class Manager {

    public:

        static types::Boolean* createBoolean(bool value);

        //static types::Dictionary* createDictionary();

        //static types::Float* createFloat(float value);

        //static types::Integer* createInteger(int value);

        //static types::List* createList();

        static types::Null* createNull();

        /// <summary>
        /// 创建一个object类型对象
        /// </summary>
        static types::Object* createObject();

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        static types::String* createString(std::string value);

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

        static void pushVariable(types::Object* value);

    protected:
        static std::vector<types::Object*> variables;

    };

}