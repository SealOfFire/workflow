#pragma once

#include <string>
#include <vector>
#include <map>
#include "../types/object.h"
#include "../../exportLib.h"

using namespace std;
using namespace workflow::ast::types;

namespace workflow::ast::executors {

    /// <summary>
    /// TODO 可删除
    /// 变量列表
    /// 执行容器型语句的时候压入当前容器的的变量列表
    /// 执行结束后弹出参数列表
    /// 可以删除
    /// </summary>
    class SHARED_LIB_API VariableStack {
    public:
        /// <summary>
        /// 变量列表，容器内的语句使用同一层级的作用域变量
        /// 变量栈，
        /// 执行容器型语句的时候压入当前容器的的变量列表
        /// 执行结束后弹出参数列表
        /// </summary>
        vector<map<string, Object*>> variables;

        void push(map<string, Object*> value);

        void pop();

        /// <summary>
        /// 获取最外层变量值
        /// </summary>
        Object* getValue(string name);

        /// <summary>
        /// 设置最外层变量值
        /// 值存在的时候更新值
        /// 值不存在的时候创建值
        /// </summary>
        void setValue(string name, Object* value);

    };
}