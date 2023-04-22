// workflow.cpp: 定义应用程序的入口点。
//

#include "workflow.h"

#define HAVE_SNPRINTF
//#include <Python.h>
#ifdef _DEBUG
#undef _DEBUG

#include <Python.h>

#define _DEBUG
#else
#include <Python.h>
#endif

#include "logger.cpp"

// ast
// ast执行器引用
#include "ast/executor/executor.h"
#include "ast/executor/executeThread.h"
// ast的表达式和语句和数据类型引用
#include "ast/includeAST.h"

#include "test/test1.hpp"
#include "test/test2.hpp"
#include "test/test3.hpp"
#include "test/test4.hpp"

using namespace std;

int main() {
    initLogger();

    cout << "Hello CMake." << endl;

    //test1();
    //test2();
    //test3();
    test4();

    cout << "执行结束" << endl;

    return 0;
}
