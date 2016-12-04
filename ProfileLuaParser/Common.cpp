#include "Common.h"

void stackDump (lua_State *L) 
{
  int i;
  int top = lua_gettop(L);
  for (i = 1; i <= top; i++) {  /* repeat for each level */
    int t = lua_type(L, i);
    switch (t) {

    case LUA_TSTRING:  /* strings */
      printf("`%s'", lua_tostring(L, i));
      break;

    case LUA_TBOOLEAN:  /* booleans */
      printf(lua_toboolean(L, i) ? "true" : "false");
      break;

    case LUA_TNUMBER:  /* numbers */
      printf("%g", lua_tonumber(L, i));
      break;

    default:  /* other values */
      printf("%s", lua_typename(L, t));
      break;

    }
    printf("  ");  /* put a separator */
  }
  printf("\n");  /* end the listing */
}

/* assume that table is on the stack top */
bool getfield(lua_State *L, size_t index, double& value)
{
  lua_pushnumber(L, index);
  lua_gettable(L, -2);  /* get background[key] */
  if (!lua_isnumber(L, -1))
    return false;
  value = lua_tonumber(L, -1);
  lua_pop(L, 1);  /* remove number */
  return true;
}

/* assume that table is on the stack top */
bool getfield(lua_State *L, const char *key, double& value)
{
  lua_pushstring(L, key);
  lua_gettable(L, -2);  /* get background[key] */
  if (!lua_isnumber(L, -1))
    return false;
  value = lua_tonumber(L, -1);
  lua_pop(L, 1);  /* remove number */
  return true;
}

/* assume that table is on the stack top */
bool getfield(lua_State *L, const char *key, std::string& value)
{
  lua_pushstring(L, key);
  lua_gettable(L, -2);  /* get background[key] */
  if (!lua_isstring(L, -1))
    return false;
  value = lua_tostring(L, -1);
  lua_pop(L, 1);  /* remove number */
  return true;
}

/* assume that table is at the top */
void setfield (lua_State *L, const char *key, double value) 
{
  lua_pushstring(L, key);
  lua_pushnumber(L, value);
  lua_settable(L, -3);
}