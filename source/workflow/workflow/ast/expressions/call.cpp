#include "call.h"
#include "../exceptions/keyNotFoundException.h"
#include "../exceptions/nullReferenceException.h"
#include "../modules/functionDefinition.h"
#include "../modules/module.h"

using namespace std;
using namespace workflow::ast::modules;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="name">函数名</param>
    Call::Call(string functionName, map<string, Expression*> arguments) :functionName(functionName), arguments(arguments) {
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="modeuleName"></param>
    /// <param name="functionName"></param>
    /// <param name="arguments"></param>
    Call::Call(string modeuleName, string functionName, map<string, Expression*> arguments) :modeuleName(modeuleName), functionName(functionName), arguments(arguments) {
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* Call::execute(Context* context) {
        //return context->variables[this->id];

        Module* module = nullptr;
        if (this->modeuleName.empty()) {
            module = context->currentModule;
        }
        else
        {
            module = context->currentModule->modules[this->modeuleName];
        }

        if (module == nullptr) {
            throw ast::exceptions::NullReferenceException(this, EXPECTION_MESSAGE_CALL_MODULE + this->modeuleName);
        }

        if (module->functions.count(this->functionName) == 0) {
            // 函数名称不对
            throw ast::exceptions::KeyNotFoundException(this, EXPECTION_MESSAGE_CALL_FUN_NAME + this->functionName);
        }

        // 设置输入变量值
        //FunctionDefinition* func = context->functions[this->functionName];
        FunctionDefinition* func = module->functions[this->functionName];

        // 循环入参的表达式列表，计算入参
        // 计算输入参数列表
        for (auto [name, expr] : this->arguments) {
            // TODO expr空判断
            // 计算结果直接放入函数的局域变量列表
            func->variables[name] = expr->run(context);
        }

        // 执行函数
        func->call(context);

        // 函数的返回值
        if (func->returns == nullptr) {
            // void 函数
        }
        else {
            return func->returns;
        }

        return nullptr;
    }

    string Call::getClassName() const {
        return Call::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string Call::toScriptCode(Context* context) {

        string args;
        // 计算输入参数列表
        for (auto [name, expr] : this->arguments) {
            args += expr->toScriptCode(context) + ", ";
        }

        string output("CALL ");
        if (this->modeuleName.empty()) {
            output += this->functionName;
        }
        else {
            output += this->modeuleName + "." + this->functionName;
        }
        output += "(" + args + ")";

        return output;
    }
}