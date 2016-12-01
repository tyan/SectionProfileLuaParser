#include "Point.h"
#include "Common.h"

Point readPoint(lua_State *L)
{
  Point result;
  if(getfield(L, 1, result.x) == false || getfield(L, 2, result.y) == false)
    throw "point reading error";
  return result;
}

PointArray readPointArray(lua_State *L)
{
  PointArray result;
  int top = lua_gettop(L);
  lua_pushnil(L);  /* first key */
  while (lua_next(L, top) != 0) {
    /* uses 'key' (at index -2) and 'value' (at index -1) */
    result.push_back(readPoint(L));
    /* removes 'value'; keeps 'key' for next iteration */
    lua_pop(L, 1);
  }
  return result;
}