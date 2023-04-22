/**
 *
 */
#include <iostream>
#include"PythonActivity.h"
 //#include <Python.h>
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

using namespace std;
using namespace workflow::activities;
using namespace workflow::executor;

PythonActivity::PythonActivity() :BaseActivity() {}
PythonActivity::PythonActivity(std::string title) :BaseActivity(title) {}

void PythonActivity::run(ExecuteEnvironment* executeEnvironment) {
    cout << "python run" << endl;
}