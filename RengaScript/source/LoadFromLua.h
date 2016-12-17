#pragma once
#include "Point2D.h"
#include "Polygon2D.h"
#include "ProfileParameter.h"

#include <lua.hpp>

#include <string>
#include <vector>
#include <memory>

namespace script
{
  namespace lua
  {
    void stackDump (lua_State *L) ;

    /* assume that table is on the stack top */
    bool getfield(lua_State *L, size_t index, double& value);

    /* assume that table is on the stack top */
    bool getfield(lua_State *L, const char *key, double& value);

    /* assume that table is on the stack top */
    bool getfield(lua_State *L, const char *key, std::string& value);

    /* assume that table is at the top */
    void setfield (lua_State *L, const char *key, double value);

    /* assume that table is on the stack top */
    Point2D readPoint(lua_State *L);

    /* assume that table is on the stack top */
    std::vector<Point2D> readPointArray(lua_State *L);

    /* assume that table is on the stack top */
    std::shared_ptr<Polygon2D> readPolygon(lua_State *L);

    /* assume that table is on the stack top */
    std::vector<ProfileParameter> readParams(lua_State *L);

    void writeParams(const std::vector<ProfileParameter>& params, lua_State *L);

    /* assume that table is on the stack top */
    std::vector<std::shared_ptr<GeometryItem>> readGeometryItems(lua_State *L);
  }
}