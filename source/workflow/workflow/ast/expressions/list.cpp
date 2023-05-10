#include "list.h"
#include "../types/list.h"

namespace workflow::ast::expressions {

    List::List() {}

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* List::execute(Context* context) {
        workflow::ast::types::List* result = new workflow::ast::types::List();
        for (int i = 0; i < this->value.size(); i++) {
            result->value.push_back(this->value[i]->run(context));
        }
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="expression"></param>
    void List::push_back(Expression* expression) {
        this->value.push_back(expression);
    }

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
    string List::toScriptCode(Context* context) {
        std::string output = "[";
        for (int i = 0; i < this->value.size(); i++) {
            output += this->value[i]->toScriptCode(context) + ",";
        }
        output += "]";

        return output;
    }

}