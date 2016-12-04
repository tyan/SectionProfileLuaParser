#include "Common.h"
#include "ProfileDesc.h"
#include "ParameterDesc.h"
#include "ProfileDescOutput.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

int main (void) {
	lua_State *L= luaL_newstate();   /* opens Lua */
	luaL_openlibs(L);             /* opens the basic library */

  try
  {
    if (0 != luaL_loadfile(L, "double_tee_beam.rpfl"))
      throw "Cannot find file!\n";

    if (0 != lua_pcall(L, 0, 0, 0))
      throw "Cannot run file!\n";

    auto params = readParams(L);
    showParams(params);

    auto profile = readProfile(L);
    outputProfile(profile, std::cout);
	}
	catch(const char* msg)
	{
		std::cout << msg;
	}

	lua_close(L);
	return 0;
}