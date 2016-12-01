#pragma once
#include "IGeometryItem.h"

struct lua_State;

class Profile
{
public:
  IGeometryItemPtrArray m_items;
};

Profile readProfile(lua_State *L);
void showProfile(const Profile& profile);