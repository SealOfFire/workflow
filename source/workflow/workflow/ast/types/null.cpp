﻿#include "null.h"

using namespace std;
using namespace workflow::ast::types;

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