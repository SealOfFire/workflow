/* --------------------------------------------
 * 测试函数
 *
 * func1(val2)
 *   print("func1 A")
 *   val1 = 5
 *   return val1
 *   return val2
 *
 * -------------------------------------------- */
#pragma once
#include<map>
#include<iostream>
#include<string>
#include "../ast/executor/executor.h"
#include "../ast/executor/executeThread.h"
#include "../ast/includeAST.h"

void test4() {
    using namespace std;
    using namespace workflow::ast::expressions;
    using namespace workflow::ast::executor;
    using namespace workflow::ast::statements;
    using namespace workflow::ast::modules;
    using namespace workflow::ast::types;

    // 模块1
    Module module1("module1");

    Constant module1_constantA("\"module1 A\""); // 字符串常量A
    Print module1_printA(&module1_constantA);// 打印func1_print
    module1.addStatement(&module1_printA);

    // 函数1
    FunctionDefinition func1("func1");
    // 打印
    Constant func1_constantA("\"func1 A\""); // 字符串常量A
    Print func1_printA(&func1_constantA);// 打印func1_print
    func1.addStatement(&func1_printA); // 打印添加到函数1中

    // 变量val1
    Name func1_name_val1("val1"); // 变量val1
    Name func1_name_val2("val2"); // 变量val1

    // 定义常量
    Constant func1_constantFive("5"); // 整形常量5
    // 赋值
    Assign func1_assign(&func1_name_val1, &func1_constantFive); //  val1 = name
    func1.addStatement(&func1_assign);

    // return
    Return func1_return(&func1_name_val1); // 返回val1
    //Return func1_return(&func1_name_val2); // 返回val2
    func1.addStatement(&func1_return);

    // 函数1 添加到 模块1
    module1.addStatement(&func1);

    // 调用函数
    map<string, Expression*> arguments; // 输入参数列表
    arguments["val2"] = new Constant("9"); // func1(val2=9)
    Call call_m1_fun1("func1", arguments);
    Print func1_print_func1return(&call_m1_fun1);// 打印func1的返回值
    module1.addStatement(&func1_print_func1return); // 打印返回值添加到模块

    // ---------------------------------------------------------------------------------------

    // 模块2
    Module module2("module2");
    module1.addStatement(&module2); // 打印返回值添加到模块

    Constant module2_constant_module2("\"module2\""); // 字符串常量A
    Print module2_print_module2(&module2_constant_module2);// 打印
    module2.addStatement(&module2_print_module2); // 打印C添加到模块

    // func2
    // 函数1
    FunctionDefinition module2_func2("func2");
    module2.addStatement(&module2_func2); // 函数2添加到模块2
    // 打印
    Constant module2_func2_constant_func2("\"func2\""); // 字符串常量A
    Print module2_func2__print_constant_func2(&module2_func2_constant_func2);// 
    module2_func2.addStatement(&module2_func2__print_constant_func2); // 打印添加到函数2

    // 添加返回值
    Constant module2_func2_constant_returnValue("\"module2 func2 return aaa\""); //
    Return module2_func2_return(&module2_func2_constant_returnValue); //
    module2_func2.addStatement(&module2_func2_return); //

    // 调用函数2
    map<string, Expression*> arguments2; // 输入参数列表
    Call module2_call_fun2("func2", arguments2);
    Print module2_print_func2_call(&module2_call_fun2); //
    module2.addStatement(&module2_print_func2_call); //

    // 模块1中调用模块2的函数2
    map<string, Expression*> arguments3; // 输入参数列表
    Call module1_call_fun2("module2", "func2", arguments3);
    Print module1_print_func2_call(&module1_call_fun2); //
    module1.addStatement(&module1_print_func2_call); //

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
