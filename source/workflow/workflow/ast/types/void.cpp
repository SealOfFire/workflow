#include "void.h"

using namespace std;
using namespace workflow::ast::types;

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