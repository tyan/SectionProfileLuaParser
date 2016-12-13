#include "Common.h"
#include "ProfileDesc.h"
#include "ParameterDesc.h"
#include "ProfileDescOutput.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>

//TODO: remove global variable
std::shared_ptr<Profile> g_profile;

int rengaUpdateParams (lua_State *L) {
  if(g_profile)
  {
    g_profile->m_params["W"].defaultValue = 3000;
    updateProfileParams(*g_profile, L);
  }
  return 0;
}

std::shared_ptr<Profile> readProfile()
{
  lua_State *L= luaL_newstate();   /* opens Lua */
	luaL_openlibs(L);             /* opens the basic library */

  std::shared_ptr<Profile> result;

  try
  {
    if (0 != luaL_loadfile(L, "double_tee_beam.rpfl"))
      throw "Cannot find file!\n";

    lua_pushcfunction(L, rengaUpdateParams);
    lua_setglobal(L, "rengaUpdateParams");

    if (0 != lua_pcall(L, 0, 0, 0))
      throw "Cannot run file!\n";

    auto profile = readProfile(L);
    outputProfile(profile, std::cout);
    result.reset(new Profile(profile));
	}
	catch(const char* msg)
	{
		std::cout << msg;
	}

	lua_close(L);
  return result;
}

void writeProfile(const Profile& profile)
{
  lua_State *L= luaL_newstate();   /* opens Lua */
	luaL_openlibs(L);             /* opens the basic library */

  try
  {
    if (0 != luaL_loadfile(L, "double_tee_beam.rpfl"))
      throw "Cannot find file!\n";
    
    lua_pushcfunction(L, rengaUpdateParams);
    lua_setglobal(L, "rengaUpdateParams");

    g_profile.reset(new Profile(profile));

    if (0 != lua_pcall(L, 0, 0, 0))
      throw "Cannot run file!\n";

    auto profile = readProfile(L);
    outputProfile(profile, std::cout);

    g_profile = nullptr;
	}
	catch(const char* msg)
	{
		std::cout << msg;
	}

	lua_close(L);
}

int main (void) 
{
  auto profile = readProfile();
  if(profile)
    writeProfile(*profile);
	return 0;
}