#include "subscript.h"
#include "../exceptions/dataTypeException.h"
#include "../exceptions/exception.h"
#include "../exceptions/keyNotFoundException.h"
#include "../types/dictionary.h"
#include "../types/integer.h"
#include "../types/list.h"
#include "../types/string.h"

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
            // dict下标处理
            types::Dictionary* dict = (types::Dictionary*)resultValue;
            if (resultSlice->getClassName() == types::String::className) {
                types::String* key = (types::String*)resultSlice;
                if (dict->value.count(key->value) != 0) {
                    Object* result = dict->value[key->value];
                    return result;
                }
                else {
                    // key不存在
                    throw exceptions::KeyNotFoundException(this, key->value);
                }
            }
            else {
                // 字典的key不是字符串
                throw exceptions::DataTypeException(this, "slice", types::String::className, resultSlice->getClassName());
            }
        }
        else if (resultValue->getClassName() == types::List::className) {
            types::List* list = (types::List*)resultValue;
            // list下标处理
            if (resultSlice->getClassName() == types::Integer::className) {
                int index = ((types::Integer*)resultSlice)->value;
                if (index < list->count())
                {
                    Object* result = list->elementAt(index);
                    return result;
                }
                else {
                    // 索引下标越界。最大下标为list.value.size()。获取的下表为index
                    throw exceptions::Exception(this, "索引下标越界");
                }
            }
            else {
                // 下标数据类型不是integer
                throw exceptions::DataTypeException(this, "slice", types::Integer::className, resultSlice->getClassName());
            }
        }
        else {
            // 变量的数据类型不是list或dict
            throw exceptions::DataTypeException(this, "data type", types::List::className, resultValue->getClassName());
        }
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
