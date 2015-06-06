//
//  luaHelper.c
//  LuaTest
//
//  Created by hiz on 2015/05/20.
//  Copyright (c) 2015年 成田 輝久. All rights reserved.
//

#include "luaHelper.h"
#include "ofMain.h"

// dataフォルダの絶対パスを返す
static int l_ofDataPath(lua_State *L) {
    lua_pushstring(L, ofToDataPath("").c_str());
    return 1;
}

// 指定フォルダのファイル名リストを返す
static int l_getFileNames(lua_State *L) {
    string path = string(lua_tostring(L, 1));
    ofDirectory dir(path);
    dir.listDir();
    
    lua_newtable(L);
    int idx = 1;
    for(const ofFile &file : dir.getFiles()) {
        lua_pushstring(L, file.getFileName().c_str());
        lua_rawseti(L, 2, idx);
        idx ++;
    }
    return 1;
}

// ログ出力
static int l_log(lua_State *L) {
    string text = string(lua_tostring(L, 1));
    ofLogNotice() << "[lua]" << text << endl;
    return 0;
}

// Lua初期化
lua_State *l_setup() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    l_addFunc(L, l_ofDataPath  , "c_ofDataPath");
    l_addFunc(L, l_getFileNames, "c_getFileNames");
    l_addFunc(L, l_log         , "c_log");
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

// luaのグローバル変数keyの数値を読み込む
lua_Number l_getGlobalNumber(lua_State *L, const char *key) {
    lua_getglobal(L, key);
    int val = lua_tointeger(L, -1);
    lua_pop(L,1);
    return val;
}

// luaのグローバル変数keyの数値を読み込む
std::string l_getGlobalString(lua_State *L, const char *key) {
    lua_getglobal(L, key);
    std::string val = lua_tostring(L, -1);
    lua_pop(L,1);
    return val;
}

// luaのテーブルからキーkeyの数値を読み込む
lua_Number l_getFieldNumber(lua_State *L, int idx, const char *key) {
    lua_getfield(L, idx, key);
    int val = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return val;
}

// luaのテーブルからキーkeyの文字列を読み込む
std::string l_getFieldString(lua_State *L, int idx, const char *key) {
    lua_getfield(L, idx, key);
    std::string val = lua_tostring(L, -1);
    lua_pop(L, 1);
    return val;
}

// luaのテーブルからインデックスnの数値を読み込む
lua_Number l_getTableNumber(lua_State *L, int idx, int n) {
    lua_rawgeti(L, idx, n);
    int val = lua_tonumber(L, -1);
    lua_pop(L, 1);
    return val;
}

// luaのテーブルからインデックスnの文字列を読み込む
std::string l_getTableString(lua_State *L, int idx, int n) {
    lua_rawgeti(L, idx, n);
    std::string val = lua_tostring(L, -1);
    lua_pop(L, 1);
    return val;
}

// luaの数値型テーブルをvector<lua_Number>に読み込む
std::vector<lua_Number> l_getTableNumbers(lua_State *L, int idx) {
    size_t dataNum = lua_rawlen(L, idx);
    std::vector<lua_Number> datas;
    for(int i=0;i<dataNum;i++) {
        datas.push_back(l_getTableNumber(L, idx, i+1));
    }
    return datas;
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