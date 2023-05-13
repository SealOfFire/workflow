# coding=utf-8

import ast
from math import fabs

src = '''
a = 1
b = 2
c = a + b
'''

src1 = """
aaa[a+b]
"""
src2 = """
3+5
"""

#variables["val1"][3] = "b[""]";
#variables["val1"][3] = "b[1]";

ast_node = ast.parse(src1, '<string>', mode="eval")
ast_node2 = ast.parse(src2, '<string>', mode="eval")

name = ""
slice = 0


def test(code):
    result = False
    name = ""
    slice = 0
    ast_node = ast.parse(src1, '<string>', mode="eval")
    # 单行表达式
    if(isinstance(ast_node.body, ast.Name)):
        name = ast_node.body.id
        result = True
    elif(isinstance(ast_node.body, ast.Subscript)):
        name = ast_node.body.value.id
        # 索引的计算结果
        expr = ast.Expression(body=ast_node.body.slice)
        value = compile(expr, '<string>', "eval")
        slice = eval(value, {}, {"a": 1, "b": 2})
        result = True
    return (result, name, slice)


print(test(src1))

# print(ast.dump(ast_node))
