#include "variableStack.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::executors {
    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    void VariableStack::push(map<string, Object*> value) {
        this->variables.push_back(value);
    }

    /// <summary>
    /// 
    /// </summary>
    void VariableStack::pop() {
        this->variables.pop_back();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    Object* VariableStack::getValue(string name) {
        return this->variables.back()[name];
    }

    void VariableStack::setValue(string name, Object* value) {
        this->variables.back()[name] = value;
    }
}