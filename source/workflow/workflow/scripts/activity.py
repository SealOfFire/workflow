# coding=utf-8
import sys
"""
python组件
"""

from parameter import Parameter
print("sys.path:")
for p in sys.path:
	print(p)

#import 全局变量

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
	val1=956
	val1=95.6
	val1=not False
	val1=None
	val1=[1,2,3,["1","2","3"]]

#run()


