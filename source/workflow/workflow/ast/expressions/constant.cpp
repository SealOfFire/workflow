#include <iostream>
#include <regex>
#include "constant.h"
#include "../types/boolean.h"
#include "../types/float.h"
#include "../types/integer.h"
#include "../types/null.h"
#include "../types/string.h"

using namespace std;
using namespace workflow::ast::executor;
using namespace workflow::ast::expressions;
using namespace workflow::ast::types;

Constant::Constant(string value) : value(value) {}

/// <summary>
/// 计算表达式
/// </summary>
/// <returns></returns>
Object* Constant::execute(Context* context) {
    //Expression::execute(env);

    // 判断数组类型是否是字符串
    // 前后是否有双引号或单引号。中间包含的引号都是转移符号的引号
    // https://dev.to/xowap/the-string-matching-regex-explained-step-by-step-4lkp

    // 匹配字符串
    std::regex regexString("\"([^\"\\\\]|\\\\.)*\"");
    //bool flag = regex_match(this->value, regexString);
    if (regex_match(this->value, regexString)) {
        // 字符串常量
        return new String(this->value);
    }

    // 匹配null
    if (this->value == "null") {
        return new Null();
    }

    // 匹配integer
    regex regexInt("^-?\\d+$");
    if (regex_match(this->value, regexInt)) {
        return new Integer(stoi(this->value));
    }

    // 匹配float
    regex regexFloat("[+-]?\\d+\\.\\d+");
    if (regex_match(this->value, regexFloat)) {
        return new Float(stof(this->value));
    }

    // 匹配bool
    if (this->value == "true") {
        return new Boolean(true);
    }
    if (this->value == "false") {
        return new Boolean(false);
    }

    // 匹配list
    // 匹配dict

    int debug = 0;
    debug++;

    // TODO 没法识别的常量。这里需要报错

    return nullptr;
}

string Constant::getClassName() const {
    return Constant::className;
}

/// <summary>
/// 转换成脚本
/// </summary>
/// <returns></returns>
string Constant::toScriptCode(Context* context) {
    //ring indent(context->indentCount * context->indentLevel, ' ');
    return this->value;
}