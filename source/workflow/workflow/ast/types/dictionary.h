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

        //std::map<std::string, Object*> value;

        Dictionary();
        ~Dictionary();

        void set(String* key, Object* value);
        void set(std::string key, Object* value);

        Object* get(String* key);
        Object* get(std::string key);

        void remove(String* key);
        void remove(std::string key);

        bool hasKey(String* key);
        bool hasKey(std::string key);

        std::map<std::string, types::Object*>::iterator begin();
        std::map<std::string, types::Object*>::iterator end();

        virtual string getClassName() const;

        virtual string toString();

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        static Dictionary* create();

    protected:
        std::map<std::string, Object*> value;

    };
}