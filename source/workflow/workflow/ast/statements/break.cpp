#include "break.h"

using namespace std;

namespace workflow::ast::statements {

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Break::getClassName()const {
        return Break::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string Break::toScriptCode(Context* context) {
        string indent(context->indentCount * context->indentLevel, ' ');
        return indent + "BREAK" + context->newline;
    }

}