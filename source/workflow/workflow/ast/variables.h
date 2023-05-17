#pragma once
#include <string>
#include <map>
#include "types/object.h"

namespace workflow::ast {

    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API Variables {

    public:
        Variables();
        ~Variables();

        bool has(std::string name);
        types::Object* get(std::string name);
        void set(std::string name, types::Object* value);
        void remove(std::string name);

        std::map<std::string, types::Object*>::iterator begin();
        std::map<std::string, types::Object*>::iterator end();

    protected:
        std::map<std::string, types::Object*> value;
    };

}