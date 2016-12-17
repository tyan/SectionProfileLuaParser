#pragma once
#include "GeometryItemImpl.h"
#include "Polygon2D.h"

#include <vector>

namespace script
{
  namespace internal
  {
    class Polygon2DImpl : public GeometryItemImpl
    {
    public:
      static Polygon2D* createPolygon(const std::vector<Point2D>& points)
      {
        return new Polygon2D(new Polygon2DImpl(points));
      }
      
      Polygon2DImpl(const std::vector<Point2D>& points)
        : m_points(points)
      {}

      ~Polygon2DImpl()
      {}

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