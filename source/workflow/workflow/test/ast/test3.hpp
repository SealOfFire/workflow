/* --------------------------------------------
 * 测试多个模块
 * module1 伪代码
 * print("module1 A")
 * print("module1 B")
 * val1=true
 * print(val1)
 * if(val1){
 *     print("is true")
 * }
 * else{
 *     print("is false")
 * }
 * 模块2和模块1同名变量作用域只在模块内
 * -------------------------------------------- */
#pragma once
#include<iostream>
#include<string>
#include "../../ast/executor/executor.h"
#include "../../ast/executor/executeThread.h"
#include "../../ast/includeAST.h"

void test3() {
    using namespace workflow::ast::expressions;
    using namespace workflow::ast::executor;
    using namespace workflow::ast::statements;
    using namespace workflow::ast::modules;
    using namespace workflow::ast::types;

    // 打印A
    Constant constantA("\"module1 A\""); // 字符串常量A
    Print printA(&constantA);// 打印

    // 打印B
    Constant constantB("\"module1 B\""); // 字符串常量A
    Print printB(&constantB);// 打印

    // 定义bool常量
    Constant constant_module1_bool("true");

    // 变量定义
    Name name_module1_val1("val1"); // 定义变量 val1
    Assign assign_module1_val1_bool(&name_module1_val1, &constant_module1_bool); // 赋值 val1=false

    // 打印val1值
    Print print_module1_val1(&name_module1_val1);// 打印

    // true时的打印
    Constant constant_module1_true("\"module1 val1 is true\"");
    Print print_module1_true(&constant_module1_true);

    // false时的打印
    Constant constant_module1_false("\"module1 val1 is false\"");
    Print print_module1_false(&constant_module1_false);

    // 条件判断
    Condition condition_module1;
    condition_module1.test = &name_module1_val1; // 变量 // if(val1)
    condition_module1.body = &print_module1_true; // then
    condition_module1.orelse = &print_module1_false; // else

    // 模块1
    Module module1("module1");
    module1.addStatement(&printA); // 打印A添加到模块
    module1.addStatement(&printB); // 打印B添加到模块
    module1.addStatement(&assign_module1_val1_bool); // 赋值语句添加到模块
    module1.addStatement(&print_module1_val1); // 打印val1添加到模块
    module1.addStatement(&condition_module1); // 条件判断添加到模块


    // 模块2 -------------------------------------------------------------------------
    // 打印A
    Constant constantC("\"module2 C\""); // 字符串常量A
    Print printC(&constantC);// 打印

    // 打印B
    Constant constantD("\"module2 D\""); // 字符串常量A
    Print printD(&constantD);// 打印

    // 定义bool常量
    Constant constant_module2_bool("false");

    // 变量定义
    Name name_module2_val1("val1"); // 定义变量 val1
    Assign assign_module2_val1_bool(&name_module2_val1, &constant_module2_bool); // 赋值 val1=false

    // 打印val1值
    Print print_module2_val1(&name_module2_val1);// 打印

    // true时的打印
    Constant constant_module2_true("\"module2 val1 is true\"");
    Print print_module2_true(&constant_module2_true);

    // false时的打印
    Constant constant_module2_false("\"module2 val1 is false\"");
    Print print_module2_false(&constant_module2_false);

    // 条件判断
    Condition condition_module2;
    condition_module2.test = &name_module2_val1; // 变量 // if(val1)
    condition_module2.body = &print_module2_true; // then
    condition_module2.orelse = &print_module2_false; // else

    Module module2("module2");
    module2.addStatement(&printC); // 打印C添加到模块
    module2.addStatement(&printD); // 打印D添加到模块
    module2.addStatement(&assign_module2_val1_bool); // 赋值语句添加到模块
    module2.addStatement(&print_module2_val1); // 打印val1添加到模块
    module2.addStatement(&condition_module2); // 条件判断添加到模块

    // 模块2添加到模块1
    module1.addStatement(&module2); // 打印B添加到模块

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