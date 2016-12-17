#pragma once
#include "GeometryItem.h"

namespace script
{
  namespace internal
  {
    class GeometryItemImpl
    {
    public:
      virtual ~GeometryItemImpl(){};
      virtual GeometryItem::Type type() const = 0;
    };
  }
}