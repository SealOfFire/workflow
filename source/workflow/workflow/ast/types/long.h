#pragma once

#include "object.h"

using namespace std;
using namespace workflow::ast;

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API Long : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_LONG;

        long value;

        Long(long value);

        virtual string getClassName() const;

        virtual string toString();

        static Long* create(long value);
    };
}