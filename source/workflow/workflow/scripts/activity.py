# coding=utf-8
"""
python组件
"""

from parameter import Parameter

# 定义输出输出参数
val1 = Parameter();
val2 = Parameter();

def run():
	"""
	执行组件
	"""
	print("activity run")
	print(val1.result)
	print(val2.result)

