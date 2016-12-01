#pragma once
#include "IGeometryItem.h"
#include "Point.h"

class Polygon : public IGeometryItem
{
public:
  PointArray m_points;
};

/* assume that table is on the stack top */
std::shared_ptr<Polygon> readPolygon(lua_State *L);