#include "binaryOperator.h"
#include "../exceptions/nullReferenceException.h"
#include "../types/boolean.h"


using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::expressions {

    /// <summary>
    /// 创建一个双目运算表达式
    /// </summary>
    /// <param name="left">左表达式</param>
    /// <param name="op">运算符</param>
    /// <param name="right">右表达式</param>
    BinaryOperator::BinaryOperator(Expression* left, Operator op, Expression* right) :left(left), op(op), right(right) {}


    /// <summary>
    /// TODO 没做完
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    Object* BinaryOperator::execute(Context* context) {
        if (this->left == nullptr) {
            throw ast::exceptions::NullReferenceException(this, EXPECTION_MESSAGE_BINARY_OP_LEFT);
        }
        Object* leftResult = this->left->run(context);


        if (this->right == nullptr) {
            throw ast::exceptions::NullReferenceException(this, EXPECTION_MESSAGE_BINARY_OP_RIGHT);
        }
        Object* rightResult = this->right->run(context);

        Object* result = nullptr;
        switch (this->op)
        {
        case Operator::Add:
            // 执行add
            result = leftResult->Add(rightResult);
            break;
        case Operator::Division:
            // TODO
            break;
        case Operator::Multiplication:
            // TODO
            break;
        case Operator::Subtraction:
            // TODO
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