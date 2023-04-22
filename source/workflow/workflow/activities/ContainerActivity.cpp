#include"ContainerActivity.h"
//#include"ActivityIterator.h"

using namespace std;
using namespace workflow::activities;
using namespace workflow::executor;

ContainerActivity::ContainerActivity() :BaseActivity("容器组件") {}
//ContainerActivity::ContainerActivity(string title) :BaseActivity(title) {}

/// <summary>
/// 序列组件析构函数
/// </summary>
ContainerActivity::~ContainerActivity()
{
    this->children.clear();
}

void ContainerActivity::run(ExecuteEnvironment* executeEnvironment) {
    // TODO
    // 遍历方式，顺序遍历，指定下一个组件id遍历

    for (BaseActivity* a : this->children) {
        a->execute(executeEnvironment);
    }
}
