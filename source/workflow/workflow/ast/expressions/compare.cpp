#include "compare.h"
#include "../types/boolean.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    Compare::Compare(Expression* left, CompareOperator compareOperator, Expression* right) :left(left), compareOperator(compareOperator), right(right) {
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* Compare::execute(Context* context) {
        Object* leftResult = this->left->run(context);
        Object* rightResult = this->right->run(context);

        bool result(false);
        switch (this->compareOperator)
        {
        case CompareOperator::Equal:
            result = ((Boolean*)leftResult)->value == ((Boolean*)rightResult)->value;
            break;
        case CompareOperator::GreaterThen:
            result = ((Boolean*)leftResult)->value > ((Boolean*)rightResult)->value;
            break;
        case CompareOperator::GreaterThenEqual:
            result = ((Boolean*)leftResult)->value >= ((Boolean*)rightResult)->value;
            break;
        case CompareOperator::In:
            break;
        case CompareOperator::Is:
            break;
        case CompareOperator::IsNot:
            break;
        case CompareOperator::LessThen:
            result = ((Boolean*)leftResult)->value < ((Boolean*)rightResult)->value;
            break;
        case CompareOperator::LessThenEqual:
            result = ((Boolean*)leftResult)->value <= ((Boolean*)rightResult)->value;
            break;
        case CompareOperator::NotEqual:
            result = ((Boolean*)leftResult)->value != ((Boolean*)rightResult)->value;
            break;
        case CompareOperator::NotIn:
            break;
        default:
            break;
        }

        //bool result = ((Boolean*)leftResult)->value && ((Boolean*)rightResult)->value;
        return new Boolean(result);
    }

    string Compare::getClassName() const {
        return  Compare::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string Compare::toScriptCode(Context* context) {
        string op;
        switch (this->compareOperator)
        {
        case CompareOperator::Equal:
            op = "==";
            break;
        case CompareOperator::GreaterThen:
            op = ">";
            break;
        case CompareOperator::GreaterThenEqual:
            op = ">=";
            break;
        case CompareOperator::In:
            op = "IN";
            break;
        case CompareOperator::Is:
            op = "IS";
            break;
        case CompareOperator::IsNot:
            op = "IS NOT";
            break;
        case CompareOperator::LessThen:
            op = "<";
            break;
        case CompareOperator::LessThenEqual:
            op = "<=";
            break;
        case CompareOperator::NotEqual:
            op = "!=";
            break;
        case CompareOperator::NotIn:
            op = "NOT IN";
            break;
        default:
            break;
        }

        return this->left->toScriptCode(context) + " " + op + " " + this->right->toScriptCode(context);
    }

}