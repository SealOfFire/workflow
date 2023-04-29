/* --------------------------------------------
 * while循环测试
 * val1=0;
 * while(val1 < 5)
 * {
 *  print(val1)
 *  val1 = val1 +1
 * }
 * -------------------------------------------- */
#pragma once
#include<map>
#include<iostream>
#include<string>
#include "../../ast/executors/executor.h"
#include "../../ast/executors/executeThread.h"
#include "../../ast/includeAST.h"

void test5() {
    // ---------------------------------------------------------------------------------------
    // 模块1
    Module module1("module1");

    Constant module1_constant_module1("\"module1\"");
    Print module1_print_constant_module1(&module1_constant_module1);
    module1.addStatement(&module1_print_constant_module1);

    // 常量0
    Constant module1_constant_0("0");

    // 变量定义
    Name module1_name_val1("val1"); // 定义变量 val1
    Assign module1_assign_val1(&module1_name_val1, &module1_constant_0); // 赋值 val1=false
    module1.addStatement(&module1_assign_val1);

    // 打印val1值
    Print module1_print_val1(&module1_name_val1);// 打印
    module1.addStatement(&module1_print_val1);


    // 常量5
    Constant module1_constant_5("5");
    //val1<5
    Compare module1_compare_val1_lessThen_5(&module1_name_val1, CompareOperator::LessThen, &module1_constant_5);

    //
    While module1_while(&module1_compare_val1_lessThen_5);
    module1.addStatement(&module1_while);

    // while 的循环体
    Container while_body_container;
    while_body_container.addStatement(&module1_print_val1); // print(val1)
    module1_while.body = &while_body_container;


    // 常量1
    Constant module1_constant_1("1");
    //val1+1
    BinaryOperator while_body_binaryOperator(&module1_name_val1, Operator::Add, &module1_constant_1);
    //val1 = val1+1
    Assign module1_assign_val2(&module1_name_val1, &while_body_binaryOperator);
    while_body_container.addStatement(&module1_assign_val2);

    // break
    Break while_break1;
    while_body_container.addStatement(&while_break1);

    // ---------------------------------------------------------------------------------------
    // 打印脚本
    Context context;
    cout << module1.toScriptCode(&context);

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