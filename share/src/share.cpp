#define EXTENSION_NAME share
#define LIB_NAME "share"
#define MODULE_NAME "share"

#define DLIB_LOG_DOMAIN LIB_NAME
#include <dmsdk/sdk.h>

#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_OSX) || defined(DM_PLATFORM_HTML5)

#include "share_private.h"

static int share_text(lua_State* L) {
    const char* text = luaL_checkstring(L, 1);
    platform_share_text(text);
    return 0;
}

static int share_image(lua_State* L) {
    size_t len;
    const char* bytes = lua_tolstring(L, 1, &len);
    const char* text = 0;
    const char* name = 0;
    if (lua_type(L, 2) == LUA_TSTRING) {
        text = luaL_checkstring(L, 2);
    }
    if (lua_type(L, 3) == LUA_TSTRING) {
        name = luaL_checkstring(L, 3);
    }
    platform_share_image(bytes, len, text, name);
    return 0;
}

static int share_file(lua_State* L) {
    const char* path = luaL_checkstring(L, 1);
    const char* text = 0;
    ShareFileInfo *info = new ShareFileInfo;
    if (lua_type(L, 2) == LUA_TSTRING) {
        text = luaL_checkstring(L, 2);
    }
    if (lua_type(L, 3) == LUA_TTABLE) {
        lua_getfield(L, 3, "text");
        lua_getfield(L, 3, "url");
        lua_getfield(L, 3, "title");
        lua_getfield(L, 3, "type");
        if  (lua_type(L, -4) == LUA_TSTRING) {
            info->text = luaL_checkstring(L, -4);
        }
        if  (lua_type(L, -3) == LUA_TSTRING) {
            info->url = luaL_checkstring(L, -3);
        }
        if  (lua_type(L, -2) == LUA_TSTRING) {
            info->title = luaL_checkstring(L, -2);
        }
        if  (lua_type(L, -1) == LUA_TSTRING) {
            info->type = luaL_checkstring(L, -1);
        }
    }
    platform_share_file(path, text, info);
    return 0;
}

static const luaL_reg Module_methods[] =
{
    {"text", share_text},
    {"image", share_image},
    {"file", share_file},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}
#else

static void LuaInit(lua_State* L) {}

#endif

dmExtension::Result AppInitializeShare(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeShare(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeShare(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeShare(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeShare, AppFinalizeShare, InitializeShare, 0, 0, FinalizeShare)
