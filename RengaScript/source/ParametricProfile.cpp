#include <ParametricProfile.h>

using namespace script;
class ParametricProfile::Impl
{
public:
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
