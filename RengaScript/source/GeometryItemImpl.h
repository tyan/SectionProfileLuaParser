#pragma once
#include "GeometryItem.h"

namespace script
{
  namespace internal
  {
    class GeometryItemImpl
    {
    public:
      virtual ~GeometryItemImpl() = 0;
      virtual GeometryItem::Type type() const = 0;
    };
  }
}