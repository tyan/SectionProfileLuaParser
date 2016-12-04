#include "ParameterDesc.h"

#include <iostream>

Param readParam(lua_State *L)
{
  Param result;

  if(!getfield(L, "name", result.name))
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
      result.type = Param::e_Real;
    else if(sType == "angle")
      result.type = Param::e_Angle;
    else
      throw "unknown parameter type";
  }
  if(!getfield(L, "value", result.defaultValue))
  {
    throw "value reading error";
  }

  return result;
}

ParamsMap readParams(lua_State *L)
{
  ParamsMap result;
  lua_getglobal(L, "profile_params");

  lua_pushnil(L);  /* first key */
  while (lua_next(L, 1) != 0) {
    /* uses 'key' (at index -2) and 'value' (at index -1) */
    result[lua_tostring(L, -2)] = readParam(L);
    /* removes 'value'; keeps 'key' for next iteration */
    lua_pop(L, 1);
  }

  lua_pop(L, 1);

  return result;
}