#include <ProfileParameter.h>

using namespace script;

class ProfileParameter::Impl
{
public:
  std::string name;
  std::string userName;
  double value;
  Type type;
};

ProfileParameter::ProfileParameter(Type type, const std::string& name, const std::string& userName, double value)
  : m_pImpl(new ProfileParameter::Impl())
{
  m_pImpl->type = type;
  m_pImpl->name = name;
  m_pImpl->userName = userName;
  m_pImpl->value = value;
}

ProfileParameter::~ProfileParameter()
{
  delete m_pImpl;
}

ProfileParameter::Type ProfileParameter::type() const
{
  return m_pImpl->type;
}

std::string ProfileParameter::name() const
{
  return m_pImpl->name;
}

std::string ProfileParameter::userName() const
{
  return m_pImpl->userName;
}

double ProfileParameter::value() const
{
  return m_pImpl->value;
}

void ProfileParameter::setValue(double value)
{
  m_pImpl->value = value;
}
