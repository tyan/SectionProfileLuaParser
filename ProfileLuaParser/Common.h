#pragma once

#include <lua.hpp>

#include <string>

void stackDump (lua_State *L) ;

/* assume that table is on the stack top */
bool getfield(lua_State *L, size_t index, double& value);

/* assume that table is on the stack top */
bool getfield(lua_State *L, const char *key, double& value);

/* assume that table is on the stack top */
bool getfield(lua_State *L, const char *key, std::string& value);