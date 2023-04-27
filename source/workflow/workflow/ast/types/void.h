#pragma once
#include "object.h"

using namespace std;
using namespace workflow::ast;

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    class SHARED_LIB_API Void : public Object {
    public:
        static constexpr const char* className = CLASS_NAME_VOID;

        virtual string getClassName() const;

        virtual string toString();
    };
}