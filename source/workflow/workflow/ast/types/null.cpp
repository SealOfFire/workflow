#include "null.h"

using namespace std;

namespace workflow::ast::types {

    Null* Null::create() {
        Null* result = new Null();
        result->autoRelease = false;
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Null::getClassName() const {
        return Null::className;
    }

    string Null::toString() {
        return Null::className;
    }
}