#include "assign.h"
#include "../exceptions/exception.h"
#include "../expressions/name.h"
#include "../expressions/subscript.h"
#include "../modules/module.h"
#include "../types/dictionary.h"
#include "../types/integer.h"
#include "../types/list.h"
#include "../types/string.h"

using namespace workflow::ast::executors;
using namespace workflow::ast::expressions;
using namespace workflow::ast::types;

namespace workflow::ast::statements {

    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="target"></param>
    /// <param name="value"></param>
    Assign::Assign(Expression* target, Expression* value) : target(target), value(value) {}

    /// <summary>
    /// 运行组件赋值过程
    /// </summary>
    void Assign::execute(Context* context) {
        // 赋值。常量赋值给变量， 变量赋值给变量，计算的结果赋值给变量
        // 这里要考虑合适new 新的存储空间，何时传递指针
        // TODO 赋值改变数据类型的变量的时候，应该delete旧的变量。防止泄露

        if (this->target->getClassName() == Name::className) {
            // target是变量名
            // 变量名
            string name = ((Name*)this->target)->id;

            // 在变量存储空间中修改变量名对应的值
            //context->variables.setValue(name, this->value->run(context));
            Object* result = this->value->run(context);
            //context->currentModule->variables[name] = result;
            context->currentModule->setVariable(name, result);
        }
        else if (this->target->getClassName() == expressions::Subscript::className) {
            // 字典。或者数组下标赋值
            // dict["key"]=
            // list[1]=
            expressions::Subscript* targerSubscript = (expressions::Subscript*)this->target;
            Object* valueResult = this->value->run(context);
            //valueResult->increaseReferenceCount();

            if (targerSubscript->value->getClassName() == expressions::Name::className) {
                expressions::Name* name = (expressions::Name*)targerSubscript->value;
                //Object* target = context->currentModule->variables[name->id];
                Object* target = context->currentModule->getVariable(name->id); // 根据名字获取局部变量
                Object* sliceResult = targerSubscript->slice->run(context);
                if (target->getClassName() == types::Dictionary::className) {
                    // 局部变量是字典
                    if (sliceResult->getClassName() == types::String::className) {
                        //((types::Dictionary*)target)->value[((types::String*)slice)->value] = result;
                        ((types::Dictionary*)target)->set((types::String*)sliceResult, valueResult);
                    }
                    else {
                        // TODO 下标不是字符串
                        throw exceptions::Exception(this, "下标不是字符串");
                    }
                }
                else if (target->getClassName() == types::List::className) {
                    // 局部变量是list
                    if (sliceResult->getClassName() == types::Integer::className) {
                        ((types::List*)target)->insert(((types::Integer*)sliceResult)->value, valueResult);
                        //((types::List*)target)->value[((types::Integer*)slice)->value] = result;
                    }
                    else {
                        // TODO  下标不是整形
                        throw exceptions::Exception(this, "下标不是整形");
                    }
                }

                Object::release(sliceResult);
            }
            else {
                // TODO 下标不是标记的变量
                throw exceptions::Exception(this, "赋值目标不是变量名");
            }
        }
        else {
            // TODO 赋值类型错误
            throw exceptions::Exception(this, "赋值类型错误");
        }

    }

    string Assign::getClassName() const {
        return Assign::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string Assign::toScriptCode(Context* context) {
        string indent(context->indentCount * context->indentLevel, ' ');
        return indent + this->target->toScriptCode(context) + " = " + this->value->toScriptCode(context) + context->newline;
    }
}