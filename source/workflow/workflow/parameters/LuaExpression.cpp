#include"LuaExpression.h"
#include "../lua/lua.hpp"

using namespace  workflow::parameters;

LuaExpression::LuaExpression(string value) :Expression(value) {}

/// <summary>
/// 计算脚本
/// </summary>
/// <param name="executeEnvironment"></param>
void LuaExpression::calculate(ExecuteEnvironment* executeEnvironment) {
    lua_pushstring(executeEnvironment->luaState, "hello world");
    lua_call(executeEnvironment->luaState, 1, 0);
}