#pragma once

namespace workflow::ast {

    /// <summary>
    /// 计算符 TODO 缺少更多的实现
    /// </summary>
    enum Operator {
        Add,
        Subtraction,
        Multiplication,
        Division,
    };

    /// <summary>
    /// 比较运算符
    /// </summary>
    enum CompareOperator {
        Equal,
        NotEqual,
        LessThen,
        LessThenEqual,
        GreaterThen,
        GreaterThenEqual,
        Is,
        IsNot,
        In,
        NotIn,
    };

    /// <summary>
    /// 运行模式
    /// </summary>
    enum ExecuteMode {
        Release,
        Debug
    };

    /// <summary>
    /// 
    /// </summary>
    enum DebugMode {
        /// <summary>
        /// 继续执行到下一个断点
        /// </summary>
        Continue,

        /// <summary>
        /// 执行一个语句
        /// </summary>
        NextStatement,

        /// <summary>
        /// 执行一个过程
        /// </summary>
        NextProcess,
    };

}