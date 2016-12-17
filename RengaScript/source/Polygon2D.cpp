#include <Polygon2D.h>
#include "Polygon2DImpl.h"

using namespace script;

Polygon2D::Polygon2D(internal::Polygon2DImpl* pImpl)
  : GeometryItem(pImpl)
{}

Polygon2D::~Polygon2D()
{}

size_t Polygon2D::pointsCount() const
{
  return impl()->m_points.size();
}

Point2D Polygon2D::point(size_t index) const
{
  return impl()->m_points.at(index);
}

void Polygon2D::addPoint(const Point2D& point)
{
  impl()->m_points.emplace_back(point);
}
