#pragma once

#include "object.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    class Boolean : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_BOOLEAN;

        bool value;

        Boolean(bool value);

        virtual string getClassName() const;

        virtual string toString();
    };
}