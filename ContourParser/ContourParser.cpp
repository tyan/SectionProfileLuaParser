#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <memory>

#include <lua.hpp>

static void stackDump (lua_State *L) 
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
bool getfield(lua_State *L, size_t index, double& value)
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

struct Point
{
	double x;
	double y;
};

typedef std::list<Point> PointArray;

Point readPoint(lua_State *L)
{
	Point result;
	if(getfield(L, 1, result.x) == false || getfield(L, 2, result.y) == false)
		throw "point reading error";
	return result;
}

class IGeometryItem
{
public:
	virtual ~IGeometryItem(){}
};

typedef std::shared_ptr<IGeometryItem> IGeometryItemPtr;
typedef std::list<IGeometryItemPtr> IGeometryItemPtrArray;

class Polygon : public IGeometryItem
{
public:
	PointArray m_points;
};

PointArray readPointArray(lua_State *L)
{
	PointArray result;
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

std::shared_ptr<Polygon> readPolygon(lua_State *L)
{
	std::shared_ptr<Polygon> result(new Polygon());
	
	lua_pushstring(L, "points");
	lua_gettable(L, -2);  /* get background[key] */
	
	result->m_points = readPointArray(L);

	lua_pop(L, 1);  /* remove number */

	return result;
}

IGeometryItemPtr readGeometryItem(lua_State *L)
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

class Profile
{
public:
	IGeometryItemPtrArray m_items;
};

void showProfile(const Profile& profile)
{

}

Profile readProfile(lua_State *L)
{
	Profile result;
	lua_getglobal(L, "profile_geometry");
  
  int top = lua_gettop(L);
	
  lua_pushnil(L);  /* first key */
	while (lua_next(L, top) != 0) {
		/* uses 'key' (at index -2) and 'value' (at index -1) */
		result.m_items.push_back(readGeometryItem(L));
		/* removes 'value'; keeps 'key' for next iteration */
		lua_pop(L, 1);
	}

	lua_pop(L, 1);

	return result;
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

	try
	{
		stackDump(L);

		//auto params = readParams(L);
		//showParams(params);

		stackDump(L);

		auto geometry = readProfile(L);
	}
	catch(const char* msg)
	{
		std::cout << msg;
	}

	lua_close(L);
	return 0;
}