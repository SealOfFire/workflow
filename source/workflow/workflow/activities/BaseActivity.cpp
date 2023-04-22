/**
 *
 */
#include <iostream>
#include <exception>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/log/trivial.hpp>
#include "BaseActivity.h"


using namespace std;
using namespace workflow::activities;
using namespace workflow::executor;

/// <summary>
/// 构造函数
/// </summary>
BaseActivity::BaseActivity() {
    boost::uuids::random_generator gen;
    this->identity = gen();
}

BaseActivity::BaseActivity(std::string title) :title(title) {
    boost::uuids::random_generator gen;
    this->identity = gen();
}

void BaseActivity::execute(ExecuteEnvironment* executeEnvironment)
{
    BOOST_LOG_TRIVIAL(trace) << "BaseActivity Execute start";
    BOOST_LOG_TRIVIAL(trace) << "BaseActivity Execute id:[" << boost::uuids::to_string(this->identity) << "]";
    BOOST_LOG_TRIVIAL(trace) << "BaseActivity Execute title:[" << this->title << "]";
    BOOST_LOG_TRIVIAL(info) << "[" << this->title << "] -- 执行开始 --";

    // 组件运行前把组件压入栈
    executeEnvironment->activityStack.insert(executeEnvironment->activityStack.begin(), this);

    try {
        this->runBefore(executeEnvironment);
        this->run(executeEnvironment);
        this->runAfter(executeEnvironment);
    }
    catch (std::exception& e) {
        BOOST_LOG_TRIVIAL(error) << "[" << this->title << "] -- 执行出错 --";
        BOOST_LOG_TRIVIAL(error) << e.what();
        if (this->errorContinueRun) {
            // 错误继续执行
            BOOST_LOG_TRIVIAL(info) << "[" << this->title << "] -- 错误继续执行-- ";
        }
        else {
            // 抛出异常时不弹出，栈顶组件就是报错的组件
            throw e;
        }
    }

    // 运行结束后弹出
    executeEnvironment->activityStack.erase(executeEnvironment->activityStack.begin());

    BOOST_LOG_TRIVIAL(info) << "[" << this->title << "] -- 执行结束 --";
    BOOST_LOG_TRIVIAL(trace) << "BaseActivity Execute end";
}

void BaseActivity::runBefore(ExecuteEnvironment* executeEnvironment) {}

void BaseActivity::run(ExecuteEnvironment* executeEnvironment)
{
    cout << "base run" << endl;
}

void BaseActivity::runAfter(ExecuteEnvironment* executeEnvironment) {}
