#pragma once
#include "RengaScript.h"
#include "GeometryItem.h"

#include <string>

namespace script
{
  class RENGA_SCRIPT_EXTERNAL ParametricProfile
  {
  public:
    ParametricProfile();
    virtual ~ParametricProfile();

    bool updateFromScript(std::string profileScriptPath);
    
    size_t geometryItemsCount() const;
    const GeometryItem* geometryItem(size_t index) const;

  private:
    class Impl;
    Impl* m_pImpl;
  };
}