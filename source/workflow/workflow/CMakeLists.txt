# CMakeList.txt: workflow 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required(VERSION 3.8)

project (workflow)
set(CMAKE_CXX_STANDARD 20)

option(SHARED_LIB_BUILD "Specifies the type of libraries (SHARED or STATIC) to build" OFF)

list(APPEND source common.h)
list(APPEND source workflow.h)
list(APPEND source workflow.cpp)

#message(source\ ${source})
# 将源代码添加到此项目的可执行文件。
add_executable(workflow ${source})

# TODO: 如有需要，请添加测试并安装目标。
if(false)
	add_subdirectory(lua)
	link_directories(lua)
	target_link_libraries(${PROJECT_NAME} lua)

	add_subdirectory(ast)
	link_directories(ast)
	target_link_libraries(${PROJECT_NAME} ast)
else()
	add_subdirectory("framework")
	#link_directories("framework")
	target_link_libraries(${PROJECT_NAME} "framework")
endif()

