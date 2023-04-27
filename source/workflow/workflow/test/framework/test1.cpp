#include <executors/context.h>
#include <modules/module.h>
#include "../framework/executors/executeThread.h"
#include "../framework/activities/pyActivity.h"

using namespace workflow::framework::activities;
using namespace workflow::framework::executors;

void test1() {

    // 模块1
    Module module1("module1");

    // 执行python组件
    PyActivity module1_pyActivity1("activity", "run");
    module1.addStatement(&module1_pyActivity1);

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
    executor.appendPythonPath("D:/MyProgram/github/workflow/source/workflow/workflow/scripts/");
    executor.execute(workflow::ast::ExecuteMode::Release); // 执行语句

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