//
//  luaHelper.c
//  LuaTest
//
//  Created by hiz on 2015/05/20.
//  Copyright (c) 2015年 成田 輝久. All rights reserved.
//

#include "luaHelper.h"
#include "ofMain.h"

// Lua初期化
lua_State *l_setup() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    return L;
}

// Luaファイル読み込み
bool l_load(lua_State *L, std::string filePath) {
    if (luaL_dofile(L, ofToDataPath(filePath).c_str())) {
        printf("%s\n", lua_tostring(L, lua_gettop(L)));
        lua_close(L);
        return false;
    }
    return true;
}


// スタックを見る
void l_printStack(lua_State *L) {
    // スタック数を取得
    const int num = lua_gettop(L);
    if (num == 0) {
        printf("No stack.\n");
        return;
    }
    for (int i = num; i >= 1; i--) {
        printf("%03d(%04d): ", i, -num + i - 1);
        int type = lua_type(L, i);
        switch(type) {
            case LUA_TNIL:
                printf("NIL\n");
                break;
            case LUA_TBOOLEAN:
                printf("BOOLEAN %s\n", lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TLIGHTUSERDATA:
                printf("LIGHTUSERDATA\n");
                break;
            case LUA_TNUMBER:
                printf("NUMBER %f\n", lua_tonumber(L, i));
                break;
            case LUA_TSTRING:
                printf("STRING %s\n", lua_tostring(L, i));
                break;
            case LUA_TTABLE:
                printf("TABLE\n");
                break;
            case LUA_TFUNCTION:
                printf("FUNCTION\n");
                break;
            case LUA_TUSERDATA:
                printf("USERDATA\n");
                break;
            case LUA_TTHREAD:
                printf("THREAD\n");
                break;
        }
    }
    printf("-----------------------------\n\n");
}

// C関数の追加
void l_addFunc(lua_State *L, lua_CFunction fnc, const char *name) {
    lua_pushcfunction(L, fnc);
    lua_setglobal(L, name);
}