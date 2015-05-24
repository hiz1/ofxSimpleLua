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



#endif /* defined(__LuaTest__luaHelper__) */
