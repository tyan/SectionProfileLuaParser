#include "LoadFromLua.h"
#include "Polygon2DImpl.h"

using namespace script;
using namespace lua;

void script::lua::stackDump (lua_State *L) 
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
bool script::lua::getfield(lua_State *L, size_t index, double& value)
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
bool script::lua::getfield(lua_State *L, const char *key, double& value)
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
bool script::lua::getfield(lua_State *L, const char *key, std::string& value)
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
void script::lua::setfield (lua_State *L, const char *key, double value) 
{
  lua_pushstring(L, key);
  lua_pushnumber(L, value);
  lua_settable(L, -3);
}

Point2D script::lua::readPoint(lua_State *L)
{
  Point2D result;
  if(getfield(L, 1, result.x) == false || getfield(L, 2, result.y) == false)
    throw "point reading error";
  return result;
}

std::vector<Point2D> script::lua::readPointArray(lua_State *L)
{
  std::vector<Point2D> result;
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

std::shared_ptr<Polygon2D> script::lua::readPolygon(lua_State *L)
{
  std::vector<Point2D> polygonPoints;

  lua_pushstring(L, "points");
  lua_gettable(L, -2);  /* get background[key] */

  polygonPoints = lua::readPointArray(L);

  lua_pop(L, 1);  /* remove number */

  return std::shared_ptr<Polygon2D>(internal::Polygon2DImpl::createPolygon(polygonPoints));
}

void readParamDesc(lua_State *L, std::string& userName, double& value, ProfileParameter::Type& type)
{
  if(!getfield(L, "name", userName))
  {
    throw "name reading error";
  }
  
  std::string sType;
  if(!getfield(L, "type", sType))
  {
    throw "type reading error";
  }
  else
  {
    if(sType == "metric")
      type = ProfileParameter::Type::Metric_mm;
    else if(sType == "angle")
      type = ProfileParameter::Type::Angle_deg;
    else
      throw "unknown parameter type";
  }
  if(!getfield(L, "value", value))
  {
    throw "value reading error";
  }
}

std::vector<ProfileParameter> script::lua::readParams(lua_State *L)
{
  std::vector<ProfileParameter> result;
  lua_getglobal(L, "params");

  lua_pushnil(L);  /* first key */
  while (lua_next(L, 1) != 0) 
  {
    std::string name;
    std::string userName;
    double value;
    ProfileParameter::Type type;

    /* uses 'key' (at index -2) and 'value' (at index -1) */
    name = lua_tostring(L, -2);
    readParamDesc(L, userName, value, type);
    /* removes 'value'; keeps 'key' for next iteration */
    lua_pop(L, 1);

    result.push_back(ProfileParameter(type, name, userName, value));
  }

  lua_pop(L, 1);

  return result;
}

// params table should be on the top of the stack
void writeParamValue(const std::string& paramName, double value, lua_State *L)
{
  lua_pushstring(L, paramName.c_str());
  lua_gettable(L, -2);  /* get background[key] */

  setfield(L, "value", value);

  lua_pop(L, 1);  /* remove number */
}

void script::lua::writeParams(const std::vector<ProfileParameter>& params, lua_State *L)
{
  lua_getglobal(L, "params");

  // writing new params
  for (auto param : params)
  {
    auto paramName = param.name();
    auto value = param.value();
    writeParamValue(paramName, value, L);
  }

  lua_pop(L, 1);
}

std::shared_ptr<GeometryItem> readGeometryItem(lua_State *L)
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

std::vector<std::shared_ptr<GeometryItem>> script::lua::readGeometryItems(lua_State *L)
{
  std::vector<std::shared_ptr<GeometryItem>> result;
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