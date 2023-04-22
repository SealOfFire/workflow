#include "binaryOperator.h"
#include "../types/boolean.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    BinaryOperator::BinaryOperator(Expression* left, Operator op, Expression* right) :left(left), op(op), right(right) {
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* BinaryOperator::execute(Context* context) {
        Object* leftResult = this->left->run(context);
        Object* rightResult = this->right->run(context);

        Object* result = nullptr;
        switch (this->op)
        {
        case Operator::Add:
            result = leftResult->Add(rightResult);
            break;
        case Operator::Division:

            break;
        case Operator::Multiplication:

            break;
        case Operator::Subtraction:

            break;
        default:
            break;
        }

         return result;
    }

    string BinaryOperator::getClassName() const {
        return  BinaryOperator::className;
    }

    /// <summary>
    /// 转换成脚本
    /// </summary>
    /// <returns></returns>
    string BinaryOperator::toScriptCode(Context* context) {
        string op;
        switch (this->op)
        {
        case Operator::Add:
            op = "+";
            break;
        case Operator::Division:
            op = "/";
            break;
        case Operator::Multiplication:
            op = "*";
            break;
        case Operator::Subtraction:
            op = "-";
            break;
        default:
            break;
        }

        return this->left->toScriptCode(context) + " " + op + " " + this->right->toScriptCode(context);
    }

}