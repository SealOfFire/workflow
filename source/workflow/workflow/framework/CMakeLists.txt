# ------------------------------------
# 组件和运行环境库
# ------------------------------------

cmake_minimum_required(VERSION 3.8)

project("framework")
set(CMAKE_CXX_STANDARD 20)

# 引用语法树子项目
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ast ${CMAKE_CURRENT_BINARY_DIR}/ast)

# 引用lua脚本
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../lua ${CMAKE_CURRENT_BINARY_DIR}/lua)

# 添加python库引用
set(Python3_ROOT_DIR "D:/Program Files/Python310")
#set(Python3_ROOT_DIR "D:/ProgramData/Anaconda3/envs/DeepAIEnviroment32")
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
message(Python\ root:[${Python3_ROOT_DIR}])
message(Python\ version:[${Python3_VERSION}])
message(Python\ includes:[${Python3_INCLUDE_DIRS}])
message(Python\ lib\ dir:[${Python3_LIBRARY_DIRS}])
message(Python\ libs:[${Python3_LIBRARIES}])
message(Python\ libs2:[${Python3_RUNTIME_LIBRARY_DIRS}])


# 项目文件
list(APPEND file_list executors/executeThread.cpp)
list(APPEND file_list executors/executor.cpp)
list(APPEND headers executors/executeThread.h)
list(APPEND headers executors/executor.h)
#
list(APPEND file_list activities/activity.cpp)
list(APPEND file_list activities/pyActivity.cpp)
list(APPEND headers activities/activity.h)
list(APPEND headers activities/pyActivity.h)
#
list(APPEND file_list expressions/luaExpression.cpp)
list(APPEND file_list expressions/pyExpression.cpp)
list(APPEND headers expressions/luaExpression.h)
list(APPEND headers expressions/pyExpression.h)
list(APPEND file_list expressions/test2.cpp)
list(APPEND file_list expressions/test2.h)
#
list(APPEND file_list types/astPyObject.cpp)
list(APPEND headers types/astPyObject.h)

list(APPEND file_list pyTools.cpp)
list(APPEND headers pyTools.h)

list(APPEND file_list test.cpp)
list(APPEND file_list test.h)

# 项目编译
add_library(${PROJECT_NAME} STATIC ${headers} ${file_list})
#add_library(${PROJECT_NAME} SHARED ${file_list})


# ast 库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../ast)
target_link_libraries(${PROJECT_NAME} ast)

#lua 库
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lua)
target_link_libraries(${PROJECT_NAME} lua)

#python3 link
target_include_directories(${PROJECT_NAME} PUBLIC ${Python3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES})

# copy dll到目标位置
# copy python的dll
# dll文件复制到指定目录
#[[
string(REPLACE "." ";" VERSION_LIST ${Python3_LIBRARIES})
message(STATUS "string = ${VERSION_LIST}")

set(pythondll ${Python3_ROOT_DIR}/python310.dll)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${PROJECT_SOURCE_DIR}/libs/$<CONFIGURATION>"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
]]