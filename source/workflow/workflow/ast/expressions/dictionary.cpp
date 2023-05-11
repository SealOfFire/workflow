#include "dictionary.h"
#include "../types/dictionary.h"
#include "../types/string.h"

namespace workflow::ast::expressions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* Dictionary::execute(Context* context) {
        workflow::ast::types::Dictionary* result = new workflow::ast::types::Dictionary();
        for (auto [key, value] : this->values) {
            Object* keyResult = key->run(context);
            Object* valueResult = value->run(context);
            if (keyResult->getClassName() == types::String::className) {
                result->value[((types::String*)keyResult)->value] = valueResult;
            }
            else {
                // TODO key不是字符串
            }
        }
        return result;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="key"></param>
    /// <param name="value"></param>
    void Dictionary::insert(Expression* key, Expression* value) {
        this->values.insert(pair<Expression*, Expression*>(key, value));
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Dictionary::getClassName() const {
        return Dictionary::className;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Dictionary::toScriptCode(Context* context) {
        std::string output = "{";
        for (auto [key, value] : this->values) {
            output += key->toScriptCode(context) + ":" + value->toScriptCode(context) + ",";
        }
        output += "}";

        return output;
    }

}