#include <ParametricProfile.h>
#include "LoadFromLua.h"

#include <vector>
#include <memory>
#include <algorithm>

using namespace script;

// twelve years of programming have led me to this wonderful global variable
std::vector<ProfileParameter> g_params;

int rengaUpdateParams (lua_State *L) {
  if(!g_params.empty())
  {
    lua::writeParams(g_params, L);
  }
  return 0;
}

class ParametricProfile::Impl
{
public:
  bool updateFromScript(std::string profileScriptPath)
  {
    bool result = false;
    g_params = m_parameters;

    lua_State *L= luaL_newstate();   /* opens Lua */
    luaL_openlibs(L);             /* opens the basic library */

    try
    {
      if (0 != luaL_loadfile(L, "double_tee_beam.rpfl"))
        throw "Cannot find file!\n";

      lua_pushcfunction(L, rengaUpdateParams);
      lua_setglobal(L, "rengaUpdateParams");

      if (0 != lua_pcall(L, 0, 0, 0))
        throw "Cannot run file!\n";

      // this means updating for the first time - parameters should be read
      // otherwise parameters have been set to profile => should not be updated
      if(m_parameters.empty())
        m_parameters = lua::readParams(L);
      m_geometryItems = lua::readGeometryItems(L);
      
      result = true;
    }
    catch(const char* /* msg*/)
    {
      // TODO: error output
    }
    catch (...)
    {
      // TODO: error output
    }
    
    lua_close(L);
    g_params.clear();

    return result;
  }

public:
  std::vector<ProfileParameter> m_parameters;

  typedef std::shared_ptr<GeometryItem> GeometryItemPtr;
  std::vector<GeometryItemPtr> m_geometryItems;
};

ParametricProfile::ParametricProfile()
  : m_pImpl(new ParametricProfile::Impl())
{
}

ParametricProfile::~ParametricProfile()
{
  delete m_pImpl;
}

bool ParametricProfile::updateFromScript(std::string profileScriptPath)
{
  return m_pImpl->updateFromScript(profileScriptPath);
}

size_t ParametricProfile::parametersCount() const
{
  return m_pImpl->m_parameters.size();
}

const ProfileParameter& ParametricProfile::parameter(size_t index) const
{
  return m_pImpl->m_parameters.at(index);
}

bool ParametricProfile::updateParameterValue(const std::string name, double value)
{
  auto paramIt = std::find_if(m_pImpl->m_parameters.begin(), 
                              m_pImpl->m_parameters.end(), 
                              [name](const ProfileParameter& parameter){return parameter.name() == name;});
  if(paramIt == m_pImpl->m_parameters.end())
    return false;

  paramIt->setValue(value);
  return true;
}

size_t ParametricProfile::geometryItemsCount() const
{
  return m_pImpl->m_geometryItems.size();
}

const GeometryItem* ParametricProfile::geometryItem(size_t index) const
{
  return m_pImpl->m_geometryItems.at(index).get();
}
