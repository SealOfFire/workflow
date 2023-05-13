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
val3 = "val3"

def run():
	"""
	执行组件
	"""
	global val1,val2,val3
	va1=[1,2,3,4];
	
	print("activity run start")
	print("val1",val1)
	print("val2",val2)
	print("val3",val3)
	val1="python change val1 value";
	val1=956
	val1=95.6
	val1=not False
	val1=None
	val1=[1,2,3,["1","2","3"]]
	val1={"key1":1,"key2":"val1","key3":[1,2,3,4]}
	val3="change by python val3"

	print("python end")
#run()


