#include "subscript.h"
#include "../types/dictionary.h"
#include "../types/integer.h"
#include "../types/list.h"

namespace workflow::ast::expressions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="value"></param>
    /// <param name="slice"></param>
    Subscript::Subscript(Expression* value, Expression* slice) :value(value), slice(slice) {}

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* Subscript::execute(Context* context) {

        Object* resultValue = this->value->run(context);
        Object* resultSlice = this->slice->run(context);
        if (resultValue->getClassName() == types::Dictionary::className) {
            // TODO
            // dict下标处理
        }
        else if (resultValue->getClassName() == types::List::className) {
            types::List* list = (types::List*)resultValue;
            // list下标处理
            if (resultSlice->getClassName() == types::Integer::className) {
                int index = ((types::Integer*)resultSlice)->value;
                if (index < list->value.size())
                {
                    Object* result = list->value[index];
                    return result;
                }
                else {
                    // TODO 索引下标越界。最大下标为list.value.size()。获取的下表为index
                }
            }
            else {
                // TODO 下标数据类型不是integer
            }
        }
        else {
            // TODO 变量的数据类型不是list或dict
        }

        return nullptr;
    }

    /// <summary>
   /// 
   /// </summary>
   /// <returns></returns>
    string Subscript::getClassName() const {
        return Subscript::className;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    string Subscript::toScriptCode(Context* context) {
        std::string output = this->value->toScriptCode(context) + "[" + this->slice->toScriptCode(context) + "]";
        return output;
    }
}
