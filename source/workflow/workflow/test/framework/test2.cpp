#include <wchar.h>
#include <executors/context.h>
#include <expressions/constant.h>
#include <expressions/dictionary.h>
#include <expressions/list.h>
#include <expressions/name.h>
#include <expressions/subscript.h>
#include <modules/module.h>
#include <statements/assign.h>
#include <statements/for.h>
#include <statements/print.h>

#include "../framework/executors/executeThread.h"
#include "../framework/activities/pyActivity.h"
#include "../framework/expressions/pyExpression.h"

using namespace workflow;
using namespace workflow::framework::activities;
using namespace workflow::framework::executors;
using namespace workflow::framework::expressions;


/// <summary>
/// list和字典类型通过下标处理数据的测试
/// value[2]=null;
/// </summary>
void test2() {
    // 模块1
    Module module1("module1");

    // 模块添加list类型局域变量
    ast::expressions::List module1_list1;
    ast::expressions::Constant module1_constant_0("1"); // int 0
    ast::expressions::Constant module1_constant_1("\"2\""); // int 0
    ast::expressions::Constant module1_constant_11("\"abc\""); // int 0
    module1_list1.push_back(&module1_constant_0);
    module1_list1.push_back(&module1_constant_1);
    module1_list1.push_back(&module1_constant_11);

    // workflow::ast::types::List module1_list1();
    // list添加数据
    ast::expressions::Name module1_name1_list1("list1"); // 定义变量 val1
    ast::statements::Assign module1_assign1_val1(&module1_name1_list1, &module1_list1); // 赋值 val1=0
    //module1_assign1_val1.breakpoint = true;
    module1.addStatement(&module1_assign1_val1);

    // 打印
    ast::statements::Print module1_print_list1(&module1_name1_list1);// 打印
    module1.addStatement(&module1_print_list1);

    // 打印list1[0]
    ast::expressions::Constant module1_constant_2("0"); // int 0
    ast::expressions::Subscript subscript0(&module1_name1_list1, &module1_constant_2);
    ast::statements::Print module1_print_list1_0(&subscript0);// 打印
    module1.addStatement(&module1_print_list1_0);

    // 遍历打印
    ast::expressions::Name module1_name1_item("item"); // 定义变量 val1
    ast::statements::Print module1_print_item(&module1_name1_item);// 打印
    ast::statements::For module1_for(&module1_name1_item, &module1_name1_list1, &module1_print_item);
    module1.addStatement(&module1_for);

    // 字典
    ast::expressions::Dictionary module1_dict1;
    ast::expressions::Constant module1_constant_key1("\"key1\"");
    ast::expressions::Constant module1_constant_value1("1");
    ast::expressions::Constant module1_constant_key2("\"key2\"");
    ast::expressions::Constant module1_constant_value2("\"value2\"");
    module1_dict1.insert(&module1_constant_key1, &module1_constant_value1);
    module1_dict1.insert(&module1_constant_key2, &module1_constant_value2);

    ast::expressions::Name module1_name1_dict1("dict1"); // 定义变量 val1
    ast::statements::Assign module1_assign1_val2(&module1_name1_dict1, &module1_dict1); // 赋值 val1=0
    module1.addStatement(&module1_assign1_val2);

    // 打印dict
    ast::statements::Print module1_print_dict1(&module1_name1_dict1);// 打印
    module1.addStatement(&module1_print_dict1);

    // 打印dict["key1"]
    ast::expressions::Constant module1_constant_33("\"key2\""); // int 0
    ast::expressions::Subscript subscript1(&module1_name1_dict1, &module1_constant_33);
    ast::statements::Print module1_print_dict1_key1(&subscript1);// 打印
    module1.addStatement(&module1_print_dict1_key1);

    // list传入传出python


    // 打印脚本
    Context context;
    cout << module1.toScriptCode(&context);

    // 执行器
    //workflow::ast::Executor executor(&container);
    //executor.execute(workflow::ast::ExecuteMode::Debug); // 执行语句

    // 在子线程上执行
    // workflow::ast::executor::ExecuteThread  executor(&container); // 执行根是容器组件
    workflow::framework::executors::ExecuteThread executor(&module1); // 执行的根是模块组件
    executor.appendPythonPath("D:/MyProgram/github/workflow/source/workflow/workflow/scripts/");
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