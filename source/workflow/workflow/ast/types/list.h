#pragma once
#include <vector>
#include "object.h"

namespace workflow::ast::types {
    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API List : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_LIST;

        std::vector<Object*> value;

        List();

        virtual string getClassName() const;

        virtual string toString();
    };
}