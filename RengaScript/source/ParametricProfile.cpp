#include <ParametricProfile.h>

#include <vector>
#include <memory>
#include <algorithm>

using namespace script;
class ParametricProfile::Impl
{
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
  return false;
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
