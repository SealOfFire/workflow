#include "void.h"

using namespace std;

namespace workflow::ast::types {

    Void* Void::create() {
        Void* result = new Void();
        result->autoRelease = false;
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Void::getClassName() const {
        return Void::className;
    }

    string Void::toString() {
        return Void::className;
    }
}