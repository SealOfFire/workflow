# coding=utf-8
"""
python组件
"""

from parameter import Parameter

# 定义输出输出参数
val1 = "value1";
val2 = "value2"

def run():
	"""
	执行组件
	"""
	global val1
	print("activity run")
	print(val1)
	print(val2)
	val1="python change val1 value";

#run()
