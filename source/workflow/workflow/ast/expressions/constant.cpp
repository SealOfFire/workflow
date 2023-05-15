#include <iostream>
#include <regex>
#include "constant.h"
//#include "../ast.h"
#include "../exceptions/exception.h"
#include "../types/boolean.h"
#include "../types/float.h"
#include "../types/integer.h"
#include "../types/null.h"
#include "../types/string.h"

using namespace std;

namespace workflow::ast::expressions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    Constant::Constant(string value) : value(value) {}

    /// <summary>
    /// 计算表达式
    /// </summary>
    /// <returns></returns>
    types::Object* Constant::execute(executors::Context* context) {
        //Expression::execute(env);
        // TODO 正则匹配的表达式改成静态常量
        // 判断数组类型是否是字符串
        // 前后是否有双引号或单引号。中间包含的引号都是转移符号的引号
        // https://dev.to/xowap/the-string-matching-regex-explained-step-by-step-4lkp

        // 匹配字符串
        std::regex regexString("\"([^\"\\\\]|\\\\.)*\"");
        //bool flag = regex_match(this->value, regexString);
        if (regex_match(this->value, regexString)) {
            // 字符串常量
            // 去掉前后的引号转义
            //std:string val2 = this->value.substr(1, this->value.size() - 2);
            return new String(this->value.substr(1, this->value.size() - 2));
            //return Manager::createString(this->value.substr(1, this->value.size() - 2));
        }

        // 匹配null
        if (this->value == "null") {
            return new Null();
            //return Manager::createNull();
        }

        // 匹配integer
        regex regexInt("^-?\\d+$");
        if (regex_match(this->value, regexInt)) {
            return new Integer(stoi(this->value));
            //return Manager::createInteger(stoi(this->value));
        }

        // 匹配float
        regex regexFloat("[+-]?\\d+\\.\\d+");
        if (regex_match(this->value, regexFloat)) {
            return new Float(stof(this->value));
            //return Manager::createFloat(stof(this->value));
        }

        // 匹配bool
        if (this->value == "true") {
            types::Boolean* result = new Boolean(true);
            //Manager::pushVariable(result);
            return result;
            //return Manager::createBoolean(true);
        }
        if (this->value == "false") {
            return new Boolean(false);
            //return Manager::createBoolean(false);
        }

        // 匹配list
        // 匹配dict

        // 没法识别的常量。这里需要报错
        throw exceptions::Exception(this, "没法识别的常量:" + this->value);

        // return nullptr;
    }

    string Constant::getClassName() const {
        return Constant::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string Constant::toScriptCode(executors::Context* context) {
        //ring indent(context->indentCount * context->indentLevel, ' ');
        return this->value;
    }

}