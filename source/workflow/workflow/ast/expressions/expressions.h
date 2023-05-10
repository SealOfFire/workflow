#pragma once

#include<iostream>
#include<string>

#define CLASS_NAME_BINARY_OPERATOR "workflow::ast::expressions::BinaryOperator"
#define CLASS_NAME_CALL "workflow::ast::expressions::Call"
#define CLASS_NAME_COMPARE "workflow::ast::expressions::Compare"
#define CLASS_NAME_CONSTANT "workflow::ast::expressions::Constant"
#define CLASS_NAME_EXPRESSION "workflow::ast::expressions::Expression"
#define CLASS_NAME_NAME "workflow::ast::expressions::Name"
#define CLASS_NAME_EXPR_LIST "workflow::ast::expressions::List"
#define CLASS_NAME_EXPR_SUBSCRIPT "workflow::ast::expressions::Subscript"

#define EXPECTION_MESSAGE_BINARY_OP_LEFT "双目运算符的左表达式为空"
#define EXPECTION_MESSAGE_BINARY_OP_RIGHT "双目运算符的左表达式为空"
#define EXPECTION_MESSAGE_CALL_MODULE "函数调用的模块为空:"
#define EXPECTION_MESSAGE_CALL_FUN_NAME "函数调用的函数名称找不到:"

#define EXPECTION_MESSAGE_NAME_MODULE "局域变量引用，模块不存在"
#define EXPECTION_MESSAGE_NAME_ID "局域变量引用，找不到变量名:"