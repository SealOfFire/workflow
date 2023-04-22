#include "while.h"
#include "../types/boolean.h"

using namespace std;
using namespace workflow::ast::executor;
using namespace workflow::ast::types;

namespace  workflow::ast::statements {

    While::While(Expression* test) :test(test) {
    }

    /// <summary>
    ///
    /// </summary>
    void While::execute(Context* context) {
        //Boolean* result = (Boolean*)this->test->run(context);

        while (((Boolean*)this->test->run(context))->value) {
            this->body->run(context);
        }

        //delete result;
    }

    string While::getClassName() const {
        return While::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string While::toScriptCode(Context* context) {
        string indent(context->indentCount * context->indentLevel, ' ');

        string output = indent + "WHILE (" + this->test->toScriptCode(context) + ")" + context->newline;
        output += indent + "{" + context->newline;
        context->indentLevel++;

        if (this->body != nullptr) {
            output += this->body->toScriptCode(context);
        }

        context->indentLevel--;
        output += indent + "}" + context->newline;


        return output;
    }
}