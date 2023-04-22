﻿#pragma once
namespace workflow::ast {

    /// <summary>
    /// 值类型
    /// </summary>
    enum ValueType {
        Null2,
        Object2,
        Integer2,
        Float2,
        String2,
        Bool2,
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