#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <map>

#include <lua.hpp>

/* assume that table is on the stack top */
bool getfield(lua_State *L, const char *key, double& value)
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
bool getfield(lua_State *L, const char *key, std::string& value)
{
	lua_pushstring(L, key);
	lua_gettable(L, -2);  /* get background[key] */
	if (!lua_isstring(L, -1))
		return false;
	value = lua_tostring(L, -1);
	lua_pop(L, 1);  /* remove number */
	return true;
}

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
			throw "uncnown parameter type";
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
	lua_getglobal(L, "contour_params");

	lua_pushnil(L);  /* first key */
	while (lua_next(L, 1) != 0) {
		/* uses 'key' (at index -2) and 'value' (at index -1) */
		result[lua_tostring(L, -2)] = readParam(L);
		/* removes 'value'; keeps 'key' for next iteration */
		lua_pop(L, 1);
	}
	return result;
}

void showParams(const ParamsMap& params)
{
	for(auto param : params)
	{
		std::cout << param.first << "\n";
		std::cout << param.second.name << "\n";
		std::cout << param.second.type << "\n";
		std::cout << param.second.defaultValue << "\n";
	}
}

int main (void) {
	//char buff[256];
	//int error;
	lua_State *L= luaL_newstate();   /* opens Lua */
	luaL_openlibs(L);             /* opens the basic library */

	if (0 != luaL_loadfile(L, "double_tee_beam.rpfl"))
		std::cout << "Cannot find file!\n";

	if (0 != lua_pcall(L, 0, 0, 0))
		std::cout << "Cannot run file!\n";

	auto params = readParams(L);

	showParams(params);
	//while (fgets(buff, sizeof(buff), stdin) != NULL) {
	//	error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
	//		lua_pcall(L, 0, 0, 0);
	//	if (error) {
	//		fprintf(stderr, "%s", lua_tostring(L, -1));
	//		lua_pop(L, 1);  /* pop error message from the stack */
	//	}
	//}

	lua_close(L);
	return 0;
}