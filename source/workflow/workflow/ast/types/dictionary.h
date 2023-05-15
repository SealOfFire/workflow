#pragma once
#include <map>
#include "object.h"
#include "string.h"

namespace workflow::ast::types {
    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API Dictionary : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_DICT;

        std::map<std::string, Object*> value;
        //std::map<String*, Object*> value;

        Dictionary();
        ~Dictionary();

        void add(String* key, Object* value);

        virtual string getClassName() const;

        virtual string toString();

    protected:


    };
}