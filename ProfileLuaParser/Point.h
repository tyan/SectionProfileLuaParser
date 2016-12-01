#pragma once
#include <list>

struct lua_State;

struct Point
{
  double x;
  double y;
};

typedef std::list<Point> PointArray;

/* assume that table is on the stack top */
Point readPoint(lua_State *L);

/* assume that table is on the stack top */
PointArray readPointArray(lua_State *L);