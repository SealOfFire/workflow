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

    // ģ��1
    Module module1("module1");

    // ģ����Ӿ������
    // val1 = "111";
    ast::expressions::Constant module1_constant_0("\"c++\""); // int 0
    ast::expressions::Name module1_name1_val1("val1"); // ������� val1
    ast::statements::Assign module1_assign1_val1(&module1_name1_val1, &module1_constant_0); // ��ֵ val1=0
    //module1_assign1_val1.breakpoint = true;
    module1.addStatement(&module1_assign1_val1);

    // ִ��python���
    PyActivity module1_pyActivity1("activity", "run");
    module1_pyActivity1.properties["val1"] = new PyExpression("val1"); // ��ǰģ��ľ������val1���뵽python��val1��
    //module1_pyActivity1.properties["val1"] = new PyExpression("\"ccccc\""); // ���python ����ı���
    module1_pyActivity1.properties["val2"] = new PyExpression("3+5");// ���python ����ı���
    module1.addStatement(&module1_pyActivity1);

    // ��ӡast�е�val1
    // ��ӡval1ֵ
    ast::statements::Print module1_print_val1(&module1_name1_val1);// ��ӡ
    module1.addStatement(&module1_print_val1);

    // ��ӡ�ű�
    Context context;
    cout << module1.toScriptCode(&context);

    // ִ����
    //workflow::ast::Executor executor(&container);
    //executor.execute(workflow::ast::ExecuteMode::Debug); // ִ�����

    // �����߳���ִ��
    // workflow::ast::executor::ExecuteThread  executor(&container); // ִ�и����������
    workflow::framework::executors::ExecuteThread executor(&module1); // ִ�еĸ���ģ�����
    //executor.InitializePython();
    //executor.appendPythonPath(L"D:\\MyProgram\\github\\workflow\\source\\workflow\\out\\build\\x64-debug\\workflow\\python310_d.zip");
    //executor.appendPythonPath(L"D:\\Program Files\\Python310\\DLLs");
    //executor.appendPythonPath(L"D:\\Program Files\\Python310\\Lib");
    //executor.appendPythonPath(L"D:\\MyProgram\\github\\workflow\\source\\workflow\\out\\build\\x64-debug\\workflow");
    //executor.appendPythonPath(L"D:\\Program Files\\Python310");
    //executor.appendPythonPath(L"D:\\Program Files\\Python310\\lib\\site-packages");
    executor.appendPythonPath("D:/MyProgram/github/workflow/source/workflow/workflow/scripts/");
    executor.execute(workflow::ast::ExecuteMode::Debug); // ִ�����

    // ִ��������
    cout << "������ s ��һ��/p ��һ������/c ����/exit" << endl;
    while (true) {
        string str;
        cin >> str;
        if (str == "exit") {
            break;
        }
        else if (str == "s") {
            // ��һ��
            cout << "��һ��" << endl;
            executor.nextStatement();
        }
        else if (str == "c") {
            // ��������һ���ϵ�
            cout << "����" << endl;
            executor.continueExecute();
        }
        else if (str == "p") {
            // ��һ������
            cout << "��һ������" << endl;
        }
        else {
            cout << "������ s/p/c/exit" << endl;
        }
    }

    //�ȵ����н���
    executor.waitStop();
}