# coding=utf-8

import ast

src='''
a = 1
b = 2
c = a + b
'''

src1="a[3]"

variables["val1"][3] = "b[""]";
variables["val1"][3] = "b[1]";

ast_node = ast.parse(src1, '<string>', mode="exec")

print(ast.dump(ast_node))