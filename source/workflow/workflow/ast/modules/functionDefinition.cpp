#include "functionDefinition.h"
#include "module.h"
#include "../exceptions/exception.h"
#include "../statements/container.h"
#include "../statements/return.h"
#include "../types/void.h"

using namespace workflow::ast::expressions;
using namespace workflow::ast::statements;
using namespace workflow::ast::types;

namespace workflow::ast::modules {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"></param>
    FunctionDefinition::FunctionDefinition(std::string name) : name(name) {
    }

    /// <summary>
    /// 
    /// </summary>
    FunctionDefinition::~FunctionDefinition() {
    }

    /// <summary>
    /// 函数执行
    /// </summary>
    /// <param name="context"></param>
    void FunctionDefinition::call(Context* context) {
        // 当前模块的变量列表
        //context->variables = this->variables;
        //context->variables.push(this->variables);

        for (statements::Statement* child : this->body) {
            if (child->getClassName() == Return::className) {
                // 遇到返回语句的时候
                if (((Return*)child)->value == nullptr) {
                    // void 函数
                    this->returns = Void::create();
                }
                else {
                    // 返回值
                    Object* returnValue = ((Return*)child)->value->run(context);
                    this->returns = returnValue;
                }
                break;
            }
            else {
                child->run(context);
            }
        }

        context->variables.pop();

        // TODO 执行到这里的时候说明函数中缺少return
        // cout << "函数中缺少return" << endl;
    }

    /// <summary>
    /// 执行语句
    /// </summary>
    void FunctionDefinition::execute(Context* context) {

        // 处理函数定义

        // 添加到父类模块的函数列表中
        if (context->currentModule == nullptr) {
            throw exceptions::Exception(this, "函数定义不是在module中");
        }
        else {
            context->currentModule->setFunction(this->name, this);
        }

        //if (this->parent != nullptr) {
        //    if (this->parent->getClassName() == Module::className) {
        //        //((Module*)this->parent)->functions[this->name] = this;
        //        ((Module*)this->parent)->setFunction(this->name, this);
        //    }
        //    else {
        //        throw exceptions::Exception(this, "函数定义不是在module中");
        //    }
        //}
        //else {
        //    throw exceptions::Exception(this, "函数定义不是在module中");
        //}
    }

    std::string FunctionDefinition::getClassName() const {
        return FunctionDefinition::className;
    }

    void FunctionDefinition::addStatement(Statement* statement) {
        this->body.push_back(statement);
    }

    std::string FunctionDefinition::toScriptCode(Context* context) {
        std::string indent(context->indentCount * context->indentLevel, ' ');

        std::string output = indent + "FUNCTION " + this->name + context->newline;
        output += indent + "{" + context->newline;
        context->indentLevel++;

        for (Statement* child : this->body) {
            output += child->toScriptCode(context);
        }

        context->indentLevel--;
        output += indent + "}" + context->newline;


        return output;
    }

    //bool FunctionDefinition::hasVariable(std::string name) {
    //    if (this->variables.count(name) == 0) {
    //        return false;
    //    }
    //    else {
    //        return true;
    //    }
    //}

    //void FunctionDefinition::setVariable(std::string name, types::Object* value) {
    //    if (this->hasVariable(name)) {
    //        Object* oldValue = this->variables[name];
    //        oldValue->decreaseReferenceCount();
    //        Object::release(oldValue);
    //    }
    //    value->increaseReferenceCount();
    //    this->variables[name] = value;
    //}
}