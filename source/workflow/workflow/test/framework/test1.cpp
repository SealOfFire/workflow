#include <executors/context.h>
#include <modules/module.h>
#include "../framework/executors/executeThread.h"
#include "../framework/activities/pyActivity.h"

using namespace workflow::framework::activities;
using namespace workflow::framework::executors;

void test1() {

    // ģ��1
    Module module1("module1");

    // ִ��python���
    PyActivity module1_pyActivity1("activity", "run");
    module1.addStatement(&module1_pyActivity1);

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
    executor.appendPythonPath("D:/MyProgram/github/workflow/source/workflow/workflow/scripts/");
    executor.execute(workflow::ast::ExecuteMode::Release); // ִ�����

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