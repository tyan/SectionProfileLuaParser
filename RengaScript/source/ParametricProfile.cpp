#include <ParametricProfile.h>

#include <vector>
#include <memory>

using namespace script;
class ParametricProfile::Impl
{
public:
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

size_t script::ParametricProfile::geometryItemsCount() const
{
  return m_pImpl->m_geometryItems.size();
}

const GeometryItem* script::ParametricProfile::geometryItem(size_t index) const
{
  return m_pImpl->m_geometryItems.at(index).get();
}
