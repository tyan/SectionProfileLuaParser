#pragma once
#include "RengaScript.h"
#include "GeometryItem.h"
#include "Point2D.h"

namespace script
{
  FORWARD_INTERNAL_IMPL(Polygon2D)

  class RENGA_SCRIPT_EXTERNAL Polygon2D : public script::GeometryItem
  {
  public:
    ~Polygon2D();

    size_t pointsCount() const;
    Point2D point(size_t index) const;
    void addPoint(const Point2D& point);

    DECLARE_PRIVATE_IMPL_FUNC(Polygon2D)
    DECLARE_NO_DEFAULT_CONSTRUCTOR(Polygon2D)
    DECLARE_NO_COPY(Polygon2D)
  };
}