#include "ProfileDesc.h"
#include "Common.h"
#include "PolygonDesc.h"

IGeometryItemPtr readGeometryItem(lua_State *L)
{
  std::string typeName;
  if(!getfield(L, "type", typeName))
    throw "error while reading ";
  if(typeName == "polygon")
  {
    return readPolygon(L);
  }
  else
  {
    throw "unknown geometry item type";
  }
}

IGeometryItemPtrArray readGeometryItems(lua_State *L)
{
  IGeometryItemPtrArray result;
  lua_getglobal(L, "geometry");

  int top = lua_gettop(L);

  lua_pushnil(L);  /* first key */
  while (lua_next(L, top) != 0) {
    /* uses 'key' (at index -2) and 'value' (at index -1) */
    result.push_back(readGeometryItem(L));
    /* removes 'value'; keeps 'key' for next iteration */
    lua_pop(L, 1);
  }

  lua_pop(L, 1);

  return result;
}

Profile readProfile(lua_State *L)
{
  Profile result;
  result.m_params = readParams(L);
  result.m_items = readGeometryItems(L);
  return result;
}