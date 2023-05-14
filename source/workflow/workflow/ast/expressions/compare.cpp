#include "compare.h"
#include "../ast.h"
#include "../exceptions/dataTypeException.h"
#include "../exceptions/notImplementedException.h"
#include "../exceptions/nullReferenceException.h"
#include "../types/boolean.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="left"></param>
    /// <param name="compareOperator"></param>
    /// <param name="right"></param>
    Compare::Compare(Expression* left, CompareOperator compareOperator, Expression* right) :left(left), compareOperator(compareOperator), right(right) {
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* Compare::execute(Context* context) {

        if (this->left == nullptr) {
            throw exceptions::NullReferenceException(this, "left");
        }
        Object* leftResult = this->left->run(context);
        if (leftResult->getClassName() != types::Boolean::className) {
            throw exceptions::DataTypeException(this, "left", types::Boolean::className, leftResult->getClassName());
        }

        if (this->right == nullptr) {
            throw exceptions::NullReferenceException(this, "right");
        }
        Object* rightResult = this->right->run(context);
        if (rightResult->getClassName() != types::Boolean::className) {
            throw exceptions::DataTypeException(this, "right", types::Boolean::className, rightResult->getClassName());
        }

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
            // TODO
            throw exceptions::NotImplementedException(this, "比较运算的IN");
            break;
        case CompareOperator::Is:
            // TODO
            throw exceptions::NotImplementedException(this, "比较运算的IS");
            break;
        case CompareOperator::IsNot:
            // TODO
            throw exceptions::NotImplementedException(this, "比较运算的IS NOT");
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
        //return new Boolean(result);
        return Manager::createBoolean(result);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
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