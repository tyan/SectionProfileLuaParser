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

	if (0 != luaL_loadfile(L, "double_tee_beam.rpfl"))
		std::cout << "Cannot find file!\n";

	if (0 != lua_pcall(L, 0, 0, 0))
		std::cout << "Cannot run file!\n";

	try
	{
		stackDump(L);

		auto params = readParams(L);
		showParams(params);

		stackDump(L);

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