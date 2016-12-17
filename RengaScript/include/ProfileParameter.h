#pragma once
#include "RengaScript.h"

#include <string>

namespace script
{
  class RENGA_SCRIPT_EXTERNAL ProfileParameter
  {
  public:
    enum Type
    {
      Undefined = 0,
      Metric_mm,
      Angle_deg
    };
    ProfileParameter(Type type, const std::string& name, const std::string& userName, double value);
    ~ProfileParameter();

    Type type() const;
    std::string name() const; // unique from script
    std::string userName() const; // "readable" for user
    double value() const;
    void setValue(double value);

  private:
    class Impl;
    Impl* m_pImpl;
  };
}