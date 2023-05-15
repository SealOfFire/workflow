# ------------------------------------
# 抽象语法树库
# ------------------------------------

cmake_minimum_required (VERSION 3.8)

project (ast)
set(CMAKE_CXX_STANDARD 20)

# 项目文件列表
list(APPEND file_list exceptions/dataTypeException.cpp)
list(APPEND file_list exceptions/exception.cpp)
list(APPEND file_list exceptions/keyNotFoundException.cpp)
list(APPEND file_list exceptions/notImplementedException.cpp)
list(APPEND file_list exceptions/nullReferenceException.cpp)
# 执行器
list(APPEND file_list executors/context.cpp)
list(APPEND file_list executors/executeThread.cpp)
list(APPEND file_list executors/executor.cpp)
list(APPEND file_list executors/variableStack.cpp)
# 表达式
list(APPEND file_list expressions/binaryOperator.cpp)
list(APPEND file_list expressions/call.cpp)
list(APPEND file_list expressions/compare.cpp)
list(APPEND file_list expressions/constant.cpp)
list(APPEND file_list expressions/dictionary.cpp)
list(APPEND file_list expressions/expression.cpp)
list(APPEND file_list expressions/list.cpp)
list(APPEND file_list expressions/name.cpp)
list(APPEND file_list expressions/subscript.cpp)
list(APPEND file_list expressions/value.cpp)
# 模块
list(APPEND file_list modules/functionDefinition.cpp)
list(APPEND file_list modules/module.cpp)
# 语句
list(APPEND file_list statements/assign.cpp)
list(APPEND file_list statements/break.cpp)
list(APPEND file_list statements/condition.cpp)
list(APPEND file_list statements/container.cpp)
list(APPEND file_list statements/continue.cpp)
list(APPEND file_list statements/for.cpp)
list(APPEND file_list statements/print.cpp)
list(APPEND file_list statements/return.cpp)
list(APPEND file_list statements/statement.cpp)
list(APPEND file_list statements/while.cpp)
# 数据类型
list(APPEND file_list types/boolean.cpp)
list(APPEND file_list types/dictionary.cpp)
list(APPEND file_list types/float.cpp)
list(APPEND file_list types/integer.cpp)
list(APPEND file_list types/list.cpp)
list(APPEND file_list types/long.cpp)
list(APPEND file_list types/null.cpp)
list(APPEND file_list types/object.cpp)
list(APPEND file_list types/string.cpp)
list(APPEND file_list types/void.cpp)

list(APPEND file_list ast.cpp)
#list(APPEND file_list ast.h)
#list(APPEND file_list common.h)
#---------------------------------------------------------
list(APPEND headers exceptions/dataTypeException.h)
list(APPEND headers exceptions/exception.h)
list(APPEND headers exceptions/keyNotFoundException.h)
list(APPEND headers exceptions/notImplementedException.h)
list(APPEND headers exceptions/nullReferenceException.h)
#
list(APPEND headers executors/context.h)
list(APPEND headers executors/executeThread.h)
list(APPEND headers executors/executor.h)
list(APPEND headers executors/variableStack.h)
#
list(APPEND headers expressions/binaryOperator.h)
list(APPEND headers expressions/call.h)
list(APPEND headers expressions/compare.h)
list(APPEND headers expressions/constant.h)
list(APPEND headers expressions/dictionary.cpp)
list(APPEND headers expressions/expression.h)
list(APPEND headers expressions/expressions.h)
list(APPEND headers expressions/list.h)
list(APPEND headers expressions/name.h)
list(APPEND headers expressions/subscript.h)
list(APPEND headers expressions/value.h)
#
list(APPEND headers modules/functionDefinition.h)
list(APPEND headers modules/module.h)
list(APPEND headers modules/modules.h)
#
list(APPEND headers statements/assign.h)
list(APPEND headers statements/break.h)
list(APPEND headers statements/condition.h)
list(APPEND headers statements/container.h)
list(APPEND headers statements/continue.h)
list(APPEND headers statements/for.h)
list(APPEND headers statements/print.h)
list(APPEND headers statements/return.h)
list(APPEND headers statements/statement.h)
list(APPEND headers statements/while.h)
#
list(APPEND headers types/boolean.h)
list(APPEND headers types/dictionary.h)
list(APPEND headers types/float.h)
list(APPEND headers types/integer.h)
list(APPEND headers types/list.h)
list(APPEND headers types/long.h)
list(APPEND headers types/null.h)
list(APPEND headers types/object.h)
list(APPEND headers types/string.h)
list(APPEND headers types/types.h)
list(APPEND headers types/void.h)

list(APPEND headers ast.h)
#add_definitions(-DSHARED_LIB_EXPORT="true")

if(SHARED_LIB_BUILD)
	add_library(${PROJECT_NAME} SHARED ${headers} ${file_list}) # 动态链接库
	#target_compile_definitions(ast PUBLIC -DSHARED_LIB_BUILD)
	#target_compile_definitions(ast PRIVATE -DSHARED_LIB_EXPORT)
else()
	add_library(${PROJECT_NAME} STATIC ${headers} ${file_list}) # 静态链接库
endif()

#[[
# 导出库头文件
message(cmake\ bin\ dir:[${CMAKE_BINARY_DIR}])
#message(${INSTALL_INCLUDEDIR})

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

message(libary\ install\ dir:[${PROJECT_SOURCE_DIR}])
message(libary\ install\ dir:[${INCLUDE_INSTALL_DIR}])
message(libary\ install\ dir:[${PROJECT_BINARY_DIR}])
install(TARGETS ${PROJECT_NAME} DESTINATION ${LIBRARY_INSTALL_DIR})
install(FILES
	types/void.h
	${PROJECT_BINARY_DIR}/ast_export.h DESTINATION ${PROJECT_SOURCE_DIR}/include/
)
]]
