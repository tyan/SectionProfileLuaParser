#pragma once
#include "ParameterDesc.h"
#include "IGeometryItem.h"

struct lua_State;

class Profile
{
public:
  ParamsMap m_params;
  IGeometryItemPtrArray m_items;
};

Profile readProfile(lua_State *L);
void updateProfileParams(const Profile& profile, lua_State *L);