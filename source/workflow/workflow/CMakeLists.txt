# CMakeList.txt: workflow 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
project (workflow)
set(CMAKE_CXX_STANDARD 20)

# 打包成pyd
set(FOR_PYTHON OFF)

# 项目文件列表
list(APPEND source activities/statements/ConditionActivity.h)
list(APPEND source activities/statements/ConditionActivity.cpp)

list(APPEND source activities/BaseActivity.h)
list(APPEND source activities/BaseActivity.cpp)
list(APPEND source activities/ContainerActivity.h)
list(APPEND source activities/ContainerActivity.cpp)
list(APPEND source activities/PythonActivity.h)
list(APPEND source activities/PythonActivity.cpp)

list(APPEND source executor/ExecuteEnvironment.h)
list(APPEND source executor/Executor.h)
list(APPEND source executor/Executor.cpp)

list(APPEND source test/test1.hpp)
list(APPEND source test/test2.hpp)

#lua库
list(APPEND source lua/lauxlib.c)
#[[
list(APPEND source parameters/Expression.cpp)
list(APPEND source parameters/Expression.h)
list(APPEND source parameters/LuaExpression.cpp)
list(APPEND source parameters/LuaExpression.h)
list(APPEND source parameters/Property.h)
]]
list(APPEND source common.h)
list(APPEND source workflow.h)
list(APPEND source workflow.cpp)
if (FOR_PYTHON)
	list(APPEND source exportPython.cpp)
endif()
# 测试代码
#list(APPEND source activities/testAcivity.h)
#list(APPEND source activities/testAcivity.cpp)

#message(source\ ${source})
# 将源代码添加到此项目的可执行文件。
if (FOR_PYTHON)
	add_library(workflow MODULE ${source})
else()
	add_executable(workflow ${source})
endif()


# TODO: 如有需要，请添加测试并安装目标。
add_subdirectory(lua)
link_directories(lua)
target_link_libraries(${PROJECT_NAME} lua)

add_subdirectory(ast)
link_directories(ast)
target_link_libraries(${PROJECT_NAME} ast)

message(--------------------------------------------------------------)
set(PYTHON_ROOT D:/ProgramData/Anaconda3/envs/DeepAIEnviroment32)
set(PYTHON_INCLUDE_DIR ${PYTHON_ROOT}/include)
set(PYTHON_LIBRARY ${PYTHON_ROOT}/libs/python38.lib)
find_package(PythonLibs 3.8 REQUIRED)
message(Python\ version: ${PYTHONLIBS_VERSION_STRING})
message(Python\ includes: ${PYTHON_INCLUDE_DIRS})
message(Python\ libs: ${PYTHON_LIBRARIES})
include_directories(${PYTHON_INCLUDE_DIRS})
if (FOR_PYTHON)
	set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".pyd")
endif()
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
# dll文件复制到指定目录
set(pythondll ${PYTHON_ROOT}/python38.dll)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${pythondll} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
# --------------------------------------------------------------

message(--------------------------------------------------------------)
#set(BOOST_ROOT /home/xus/boost)
find_package(Boost 1.81.0 COMPONENTS log_setup log python38)
message(Boost\ version: ${Boost_VERSION_STRING})
message(Boost\ include\ dir: ${Boost_INCLUDE_DIRS})
message(Boost\ library\ dir: ${Boost_LIBRARY_DIRS})
#set(Boost_USE_STATIC_LIBS ON)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


#add_definitions(-DBOOST_PYTHON_STATIC_LIB) # x86 python38 时需要开启 在头文件中设置
#set(Boost_USE_STATIC_LIBS ON)
#add_definitions(-DHAVE_SNPRINTF)
