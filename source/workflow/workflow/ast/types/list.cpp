#include "list.h"

namespace workflow::ast::types {

    /// <summary>
    /// 
    /// </summary>
    List::List() {}

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
    string List::toString() {
        // return std::to_string(this->value);
        std::string output = "[";
        for (int i = 0; i < this->value.size(); i++) {
            output += this->value[i]->toString() + ", ";
        }
        output += "]";
        return output;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="item"></param>
    void List::append(Object* item) {
        this->value.push_back(item);
    }
}
