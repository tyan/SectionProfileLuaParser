#pragma once
#include "RengaScript.h"

#include <string>

namespace script
{
  class RENGA_SCRIPT_EXTERNAL ParametricProfile
  {
  public:
    ParametricProfile();
    virtual ~ParametricProfile();

    bool updateFromScript(std::string profileScriptPath);

  private:
    class Impl;
    Impl* m_pImpl;
  };
}