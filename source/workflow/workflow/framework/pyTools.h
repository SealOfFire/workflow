/* python相关的处理 */
#pragma once
#include <iostream>
#include <map>
#include <string>
#include <Python.h>
#include <types/object.h>

#pragma once
#define PY_TYPE_STRING "str"
#define PY_TYPE_INTEGER "int"
#define PY_TYPE_FLOAT "float"
#define PY_TYPE_NONE "NoneType"
#define PY_TYPE_DICTIONARY "dict"
#define PY_TYPE_LIST "list"
#define PY_TYPE_BOOLEAN "bool"
#define PY_TYPE_TUPLE "tuple"

// 用来判断python表达式，是不是变量，或者带下标的变量，变量用来交换参数
#define SOURCE1 R"ETO(
import ast
def test(code,local):
	result = False
	typeIndex = -1;
	name = ""
	slice = 0
	ast_node = ast.parse(code, "<string>", mode="eval")
	# 单行表达式
	if(isinstance(ast_node.body, ast.Name)):
		name = ast_node.body.id
		result = True
		typeIndex = 0;
	elif(isinstance(ast_node.body, ast.Subscript)):
		name = ast_node.body.value.id
		# 索引的计算结果
		expr = ast.Expression(body=ast_node.body.slice)
		value = compile(expr, "<string>", "eval")
		slice = eval(value, {}, local)
		result = True
		typeIndex = 1;
	return (result, typeIndex,name, slice)
)ETO"

namespace workflow::framework {

    /// <summary>
    /// 
    /// </summary>
    /// <param name="context"></param>
    /// <returns></returns>
    PyObject* convertAstObjectToPyObject(workflow::ast::types::Object* value);

    /// <summary>
    /// 
    /// </summary>
    workflow::ast::types::Object* convertPyObjectToAstObject(PyObject* value);

    /// <summary>
    /// ast的变量列表，转成python的字典
    /// </summary>
    /// <param name="variables"></param>
    /// <returns></returns>
    PyObject* convertAstVariablesToPyDict(std::map<std::string, ast::types::Object*> variables);

    /// <summary>
    /// 判断当前的脚本结果是不是一个变量，如果是变量要和外部做数据交换
    /// </summary>
    PyObject* createTestExpressionModule();

}
