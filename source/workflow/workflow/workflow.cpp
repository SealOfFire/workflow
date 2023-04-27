// workflow.cpp: 定义应用程序的入口点。
//

#include "workflow.h"

//#include "logger.cpp"

// ast
// ast执行器引用
//#include "ast/executor/executor.h"
//#include "ast/executor/executeThread.h"
// ast的表达式和语句和数据类型引用
//#include "ast/includeAST.h"

#define astDebug false
#if astDebug
#include "test/ast/test1.hpp"
#include "test/ast/test2.hpp"
#include "test/ast/test3.hpp"
#include "test/ast/test4.hpp"
#include "test/ast/test5.hpp"
#else
#include "framework/test.h"
#include "framework/expressions/test2.h"
#include "framework/executors/executor.h"
#include "test/framework/test1.cpp"
#endif

using namespace std;

int main() {
    //initLogger();

    cout << "Hello CMake." << endl;

#if ast
    //test1();
    //test2();
    //test3();
    //test4();
    test5();
#else
    //workflow::framework::Test test;
    //workflow::framework::expressions::Test2 test2;
    // test.init();

    test1();

    //workflow::framework::executors::Executor executor;
    //executor.InitializePython();

#endif

    cout << "执行结束" << endl;

    return 0;
}
