#pragma once

#include <iostream>
// ast执行器引用
#include "../ast/executor/executor.h"
#include "../ast/executor/executeThread.h"
// 数据类型引用
#include "../ast/includeAST.h"

void test1() {
    using namespace workflow::ast::expressions;

    // 运行环境
    Context context;

    // 产量表达式测试
    // 常量表达式
    Constant constant1("\"test 1\""); // 字符串
    //constant1.execute();
    Constant constant2("11"); // int
    Constant constant3("-11"); // int
    Constant constant4("11.2"); // float
    Constant constant5("-11.2"); // float
    Constant constant6("true"); // bool
    Constant constant7("[1,2]"); // list 不支持
    Constant constant8("{'a':'b'}"); // dict // 不支持
    Constant constant9("null"); // null

    // 变量表达式
    workflow::ast::expressions::Name name1("val1");

    // 赋值语句
    workflow::ast::statements::Assign assign1(&name1, &constant6);
    assign1.execute(&context);

    // 打印变量
    cout << ((String*)context.variables.getValue("val1"))->toString() << endl;

    // 条件语句
    workflow::ast::statements::Condition cond;
    cond.test = &constant6; // 常量 true/false
    cond.test = &name1; // 变量
    cond.body = new workflow::ast::statements::Statement();
    cond.orelse = new workflow::ast::statements::Statement();
    cond.execute(&context);

}