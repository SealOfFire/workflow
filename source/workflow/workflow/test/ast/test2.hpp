/* --------------------------------------------
 * 测试模块
 * 断点测试
 * -------------------------------------------- */
#pragma once
#include<iostream>
#include<string>
#include "../../ast/executor/executor.h"
#include "../../ast/executor/executeThread.h"
#include "../../ast/includeAST.h"

void test2() {
    using namespace workflow::ast::expressions;
    using namespace workflow::ast::executor;
    using namespace workflow::ast::statements;
    using namespace workflow::ast::modules;

    // 容器语句
    Container container;
    // 常量定义
    Constant constant("false");
    constant.breakpoint = true; // 常量false添加断点
    // 变量定义
    Name name("val1"); // 定义变量 val1
    Assign assign(&name, &constant); // 赋值 val1=false
    assign.breakpoint = true; // 赋值语句设置断点
    container.children.push_back(&assign); // 赋值语句添加到容器

    Constant constantA("\"A\""); // 字符串常量A
    Print print1(&constantA);// 打印
    Constant constantB("\"B\""); // 字符串常量A
    Print print2(&constantB); // 打印

    // 条件判断
    workflow::ast::statements::Condition condition;
    condition.test = &name; // 变量 // if(val1)
    condition.body = &print1; // then
    condition.orelse = &print2; // else
    container.children.push_back(&condition); // 条件语句添加到容器

    // 模块
    workflow::ast::modules::Module module1("test1");
    module1.addStatement(&container);

    // 执行器
    //workflow::ast::Executor executor(&container);
    //executor.execute(workflow::ast::ExecuteMode::Debug); // 执行语句

    // 在子线程上执行
    // workflow::ast::executor::ExecuteThread  executor(&container); // 执行根是容器组件
    ExecuteThread executor(&module1); // 执行的根是模块组件
    executor.execute(workflow::ast::ExecuteMode::Debug); // 执行语句

    // 执行器运行
    cout << "请输入 s 下一句/p 下一个过程/c 继续/exit" << endl;
    while (true) {
        string str;
        cin >> str;
        if (str == "exit") {
            break;
        }
        else if (str == "s") {
            // 下一步
            cout << "下一句" << endl;
            executor.nextStatement();
        }
        else if (str == "c") {
            // 继续到下一个断点
            cout << "继续" << endl;
            executor.continueExecute();
        }
        else if (str == "p") {
            // 下一个过程
            cout << "下一个过程" << endl;
        }
        else {
            cout << "请输入 s/p/c/exit" << endl;
        }
    }

    //等到运行结束
    executor.waitStop();
}