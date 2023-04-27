#pragma once

#include "object.h"

using namespace std;
using namespace workflow::ast;

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    class Integer : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_INTEGER;

        int value;

        Integer(int value);

        virtual Object* Add(Object* value);
        virtual Object Add(Object& value);

        virtual string getClassName() const;

        virtual string toString();
    };
}