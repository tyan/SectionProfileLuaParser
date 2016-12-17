#pragma once
#include "RengaScript.h"

namespace script
{
  FORWARD_INTERNAL_IMPL(GeometryItem)

  class RENGA_SCRIPT_EXTERNAL GeometryItem
  {
  public:
    virtual ~GeometryItem();

    enum Type
    {
      Undefined = 0,
      Polygon2D = 1
    };
    Type type() const;

    DECLARE_PROTECTED_IMPL(GeometryItem)
    DECLARE_NO_COPY(GeometryItem)
    DECLARE_NO_DEFAULT_CONSTRUCTOR(GeometryItem)
  };
}