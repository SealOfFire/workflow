#include <wchar.h>
#include <executors/context.h>
#include <expressions/constant.h>
#include <expressions/name.h>
#include <modules/module.h>
#include <statements/assign.h>
#include <statements/print.h>

#include "../framework/executors/executeThread.h"
#include "../framework/activities/pyActivity.h"
#include "../framework/expressions/pyExpression.h"

using namespace workflow;
using namespace workflow::framework::activities;
using namespace workflow::framework::executors;
using namespace workflow::framework::expressions;

void test1() {

    // 模块1
    Module module1("module1");

    // 模块添加局域变量
    // val1 = "111";
    ast::expressions::Constant module1_constant_0("\"c++\""); // int 0
    ast::expressions::Name module1_name1_val1("val1"); // 定义变量 val1
    ast::statements::Assign module1_assign1_val1(&module1_name1_val1, &module1_constant_0); // 赋值 val1=0
    //module1_assign1_val1.breakpoint = true;
    module1.addStatement(&module1_assign1_val1);

    // 执行python组件
    PyActivity module1_pyActivity1("activity", "run");
    module1_pyActivity1.properties["val1"] = new PyExpression("val1"); // 当前模块的局域变量val1传入到python的val1中
    //module1_pyActivity1.properties["val1"] = new PyExpression("\"ccccc\""); // 添加python 组件的变量
    module1_pyActivity1.properties["val2"] = new PyExpression("3+5");// 添加python 组件的变量
    module1.addStatement(&module1_pyActivity1);

    // 打印ast中的val1
    // 打印val1值
    ast::statements::Print module1_print_val1(&module1_name1_val1);// 打印
    module1.addStatement(&module1_print_val1);

    // 打印脚本
    Context context;
    cout << module1.toScriptCode(&context);

    // 执行器
    //workflow::ast::Executor executor(&container);
    //executor.execute(workflow::ast::ExecuteMode::Debug); // 执行语句

    // 在子线程上执行
    // workflow::ast::executor::ExecuteThread  executor(&container); // 执行根是容器组件
    workflow::framework::executors::ExecuteThread executor(&module1); // 执行的根是模块组件
    //executor.InitializePython();
    //executor.appendPythonPath(L"D:\\MyProgram\\github\\workflow\\source\\workflow\\out\\build\\x64-debug\\workflow\\python310_d.zip");
    //executor.appendPythonPath(L"D:\\Program Files\\Python310\\DLLs");
    //executor.appendPythonPath(L"D:\\Program Files\\Python310\\Lib");
    //executor.appendPythonPath(L"D:\\MyProgram\\github\\workflow\\source\\workflow\\out\\build\\x64-debug\\workflow");
    //executor.appendPythonPath(L"D:\\Program Files\\Python310");
    //executor.appendPythonPath(L"D:\\Program Files\\Python310\\lib\\site-packages");
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