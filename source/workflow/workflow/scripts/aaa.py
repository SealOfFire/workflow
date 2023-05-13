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