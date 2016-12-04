#pragma once
#include "Common.h"

#include <map>

struct Param
{
  enum Type
  {
    e_Real = 0,
    e_Angle
  };
  std::string name;
  Type type;
  double defaultValue;
};

typedef std::map<std::string, Param> ParamsMap;

ParamsMap readParams(lua_State *L);
void writeParams(const ParamsMap& params, lua_State *L);