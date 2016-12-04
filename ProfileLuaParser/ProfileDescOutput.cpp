#include "ProfileDescOutput.h"
#include "ProfileDesc.h"
#include "PolygonDesc.h"

#include <string>

class Indent
{
public:
  Indent()
  {
    g_indentSize++;
  }

  ~Indent()
  {
    g_indentSize--;
  }

  static std::string get()
  {
    return std::string(g_indentSize, g_indent);
  }

private:
  static size_t g_indentSize;
  static char g_indent;
};

size_t Indent::g_indentSize = 0;
char Indent::g_indent = ' ';

void outputPoint(const Point& point, std::ostream& os)
{
  os << Indent::get() << "Point (x=" << point.x << ", y=" << point.y << ")" << std::endl;
}

void outputPointsArray(const PointArray& points, std::ostream& os)
{
  Indent ind;
  for (auto point : points)
    outputPoint(point, os);
}

void outputPolygon(const Polygon& polygon, std::ostream& os)
{
  Indent ind;
  os << Indent::get() << "Polygon:" << std::endl;
  outputPointsArray(polygon.m_points, os);
}

void outputGeometryItems(const IGeometryItemPtrArray& items, std::ostream& os)
{
  Indent ind;
  os << Indent::get() << "Profile geometry:" << std::endl;

  for(auto pGeometryItem : items)
  {
    if(const Polygon* pPolygon = dynamic_cast<const Polygon*>(pGeometryItem.get()))
      outputPolygon(*pPolygon, os);
  }
}

void outputProfile(const Profile& profile, std::ostream& os)
{
  os << Indent::get() << "Profile description:" << std::endl;
  outputGeometryItems(profile.m_items, os);
}