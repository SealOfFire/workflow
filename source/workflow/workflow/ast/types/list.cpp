﻿#include "list.h"

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    List::List() {}

    /// <summary>
   /// 
   /// </summary>
   /// <returns></returns>
    string List::getClassName() const {
        return List::className;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string List::toString() {
        // return std::to_string(this->value);
        return "[LIST]";
    }
}