#include "module.h"
#include "../exceptions/exception.h"
#include "../statements/container.h"

namespace workflow::ast::modules {

    Module::Module(string name) :name(name) {
    }

    Module::~Module() {

        //std::map<std::string, types::Object*>::iterator iter1;
        //for (iter1 = this->variables.begin(); iter1 != this->variables.end();) {
        //    iter1->second->decreaseReferenceCount();
        //    Object::release(iter1->second);
        //    iter1->second = nullptr;
        //    this->variables.erase(iter1++);
        //}
        //this->variables.clear();

        // function 和 child module 不在系统中new。所以不在系统中delete
        std::map<std::string, FunctionDefinition*>::iterator iter2;
        for (iter2 = this->functions.begin(); iter2 != this->functions.end();) {
            //delete iter2->second;
            //iter2->second = nullptr;
            this->functions.erase(iter2++);
        }
        this->functions.clear();

        std::map<std::string, Module*>::iterator iter3;
        for (iter3 = this->childModules.begin(); iter3 != this->childModules.end();) {
            //delete iter3->second;
            //iter3->second = nullptr;
            this->childModules.erase(iter3++);
        }
        this->childModules.clear();

        //for (int i = 0; i < this->body.size(); i++) {
        //}
        this->body.clear();
    }

    /// <summary>
    /// 执行语句
    /// </summary>
    void Module::execute(executors::Context* context) {

        // 当前模块的变量列表
        //context->variables.push(this->variables);
        //context->parent = this;
        //context->modules[this->name] = this;

        //Module* parent = nullptr;
        //  if (context->currentModule != nullptr) {
        Module* parent = context->currentModule;
        // }
        context->currentModule = this;

        // 把当前模块添加到父模块列表
        if (this->parent != nullptr) {
            if (this->parent->getClassName() == Module::className) {
                ((Module*)this->parent)->childModules[this->name] = this;
            }
        }

        //
        //if (this->body != nullptr) {
        //    this->body->run(context);
        //}
        for (int i = 0; i < this->body.size(); i++) {
            this->body[i]->run(context);
        }

        // if (parent != nullptr) {
        // 当前模块运行完，当前模块切换会父模块
        context->currentModule = parent;
        //}

        // 只保留当前层内的模块，方便函数调用
        // 不能移除
        //context->modules.erase(this->name);
        //context->parent = nullptr;
        //context->variables.pop();
    }

    string Module::getClassName() const {
        return Module::className;
    }

    void Module::addStatement(statements::Statement* statement) {

        statement->parent = this;

        this->body.push_back(statement);

        //if (this->body == nullptr) {
        //    // 当前body是空，直接添加
        //    this->body = statement;
        //}
        //else if (this->body->getClassName() == Container::className) {
        //    // 当前是容器组件，直接添加
        //    ((Container*)this->body)->children.push_back(statement);
        //}
        //else {
        //    // 创建一个容器组件
        //    Container* container = new Container();
        //    container->children.push_back(this->body); // 原本的body语句
        //    container->children.push_back(statement); // 新加的语句
        //    this->body = container;
        //}
    }

    /// <summary>
    /// 向模块中添加函数
    /// </summary>
    /// <param name="name"></param>
    /// <param name="function"></param>
    //void Module::addFunction(string name, Function* function) {}

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string Module::toScriptCode(executors::Context* context) {
        string indent(context->indentCount * context->indentLevel, ' ');

        string output = indent + "MODULE " + this->name + context->newline;
        output += indent + "{" + context->newline;
        context->indentLevel++;

        //if (this->body != nullptr) {
        //    output += this->body->toScriptCode(context);
        //}
        for (int i = 0; i < this->body.size(); i++) {
            output += this->body[i]->toScriptCode(context);
        }

        context->indentLevel--;
        output += indent + "}" + context->newline;


        return output;
    }

    bool Module::hasChildModule(std::string name) {
        if (this->childModules.count(name) == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    Module* Module::getChildModule(std::string name) {
        if (this->hasChildModule(name)) {
            return this->childModules[name];
        }
        else {
            // 模块名称不存在
            throw exceptions::Exception(this, name + "子模块不存在");
        }
    }

    bool Module::hasFunction(std::string name) {
        if (this->functions.count(name) == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    FunctionDefinition* Module::getFunction(std::string name) {
        if (this->hasFunction(name)) {
            return this->functions[name];
        }
        else {
            // 模块名称不存在
            throw exceptions::Exception(this, name + "函数不存在");
        }
    }

    void Module::setFunction(std::string name, FunctionDefinition* function) {
        if (this->hasFunction(name)) {
            throw exceptions::Exception(this, name + "函数名重复");
        }
        else {
            this->functions[name] = function;
        }
    }

    bool Module::hasVariable(std::string name) {
        return this->variables.has(name);
    }

    types::Object* Module::getVariable(std::string name) {
        return this->variables.get(name);
    }

    void Module::setVariable(std::string name, types::Object* value) {
        this->variables.set(name, value);
    }

    void Module::removeVariable(std::string name) {
        this->variables.remove(name);
    }

    Variables* Module::getVariables() {
        return &this->variables;
    }

}