#include "bool_operate_expression.h"
#include "../types/boolean.h"

using namespace workflow::ast::executor;
using namespace workflow::ast::expressions;
using namespace workflow::ast::types;

/// <summary>
/// 计算表达式
/// </summary>
/// <returns></returns>
Object* BoolOperateExpression::execute(Context* context) {

    Object* leftResult = this->left->run(context);
    Object* rightResult = this->right->run(context);
    bool result = ((Boolean*)leftResult)->value && ((Boolean*)rightResult)->value;
    return new Boolean(result);
}

string BoolOperateExpression::getClassName() const {
    return "workflow::ast::expressions::BoolOperateExpression";
}