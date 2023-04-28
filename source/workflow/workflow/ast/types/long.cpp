#include "long.h"

using namespace std;

namespace workflow::ast::types {
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="value"></param>
    Long::Long(long value) : value(value) {}

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Long::getClassName() const {
        return Long::className;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Long::toString() {
        return std::to_string(this->value);
    }

}