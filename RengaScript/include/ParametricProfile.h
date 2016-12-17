#pragma once
#include "RengaScript.h"
#include "ProfileParameter.h"
#include "GeometryItem.h"

namespace script
{
  class RENGA_SCRIPT_EXTERNAL ParametricProfile
  {
  public:
    ParametricProfile();
    virtual ~ParametricProfile();

    // common logic
    bool updateFromScript(std::string profileScriptPath);

    // parameters
    size_t parametersCount() const;
    const ProfileParameter& parameter(size_t index) const;
    bool updateParameterValue(const std::string name, double value);

    // geometry
    size_t geometryItemsCount() const;
    const GeometryItem* geometryItem(size_t index) const;

  private:
    class Impl;
    Impl* m_pImpl;
  };
}