#pragma once
#include "GeometryItemImpl.h"
#include "Point2D.h"

#include <vector>

namespace script
{
  namespace internal
  {
    class Polygon2DImpl : public GeometryItemImpl
    {
    public:
      ~Polygon2DImpl();

      // GeometryItemImpl
      GeometryItem::Type type() const
      {
        return GeometryItem::Type::Polygon2D;
      }

    public:
      std::vector<Point2D> m_points;
    };
  }
}