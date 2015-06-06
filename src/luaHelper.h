//
//  luaHelper.h
//  LuaTest
//
//  Created by hiz on 2015/05/20.
//  Copyright (c) 2015Âπ¥ ÊàêÁî∞ Ëºù‰πÖ. All rights reserved.
//

#ifndef __LuaTest__luaHelper__
#define __LuaTest__luaHelper__

#include <iostream>
#include <vector>

#include "lua/lua.hpp"
#include "lua/lauxlib.h"
#include "lua/lualib.h"

// Lua初期化
lua_State *l_setup();

// Luaファイル読み込み
bool l_load(lua_State *L, std::string luaFileName);

// スタックを見る
void l_printStack(lua_State *L);

// C関数の追加
void l_addFunc(lua_State *L, lua_CFunction fnc, const char *name);

// luaのグローバル変数keyの数値を読み込む
lua_Number l_getGlobalNumber(lua_State *L, const char *key);

// luaのグローバル変数keyの文字列を読み込む
std::string l_getGlobalString(lua_State *L, const char *key);

// luaのテーブルからキーkeyの数値を読み込む
lua_Number l_getFieldNumber(lua_State *L, int idx, const char *key);

// luaのテーブルからキーkeyの文字列を読み込む
std::string l_getFieldString(lua_State *L, int idx, const char *key);

// luaのテーブルからインデックスnの数値を読み込む
lua_Number l_getTableNumber(lua_State *L, int idx, int n);

// luaのテーブルからインデックスnの文字列を読み込む
std::string l_getTableString(lua_State *L, int idx, int n);

// luaの数値型テーブルをvector<lua_Number>に読み込む
std::vector<lua_Number> l_getTableNumbers(lua_State *L, int idx);

#endif /* defined(__LuaTest__luaHelper__) */
