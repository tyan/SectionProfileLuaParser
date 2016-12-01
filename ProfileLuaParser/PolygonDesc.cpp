#include "PolygonDesc.h"
#include "Common.h"

std::shared_ptr<Polygon> readPolygon(lua_State *L)
{
  std::shared_ptr<Polygon> result(new Polygon());

  lua_pushstring(L, "points");
  lua_gettable(L, -2);  /* get background[key] */

  result->m_points = readPointArray(L);

  lua_pop(L, 1);  /* remove number */

  return result;
}