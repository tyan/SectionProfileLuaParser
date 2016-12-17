#include "ParametricProfileOutput.h"
#include "..\RengaScript\include\Polygon2D.h"

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

void outputPoint(const script::Point2D& point, std::ostream& os)
{
  os << Indent::get() << "Point (x=" << point.x << ", y=" << point.y << ")" << std::endl;
}

void outputPolygon(const script::Polygon2D& polygon, std::ostream& os)
{
  Indent ind1;
  os << Indent::get() << "Polygon:" << std::endl;
  
  Indent ind2;
  for (size_t i = 0; i < polygon.pointsCount(); ++i)
  {
    outputPoint(polygon.point(i), os);
  }
}

void outputGeometryItems(const script::ParametricProfile& profile, std::ostream& os)
{
  Indent ind;
  os << Indent::get() << "Geometry:" << std::endl;

  for (size_t i = 0; i < profile.geometryItemsCount(); ++i)
  {
    auto pGeometryItem = profile.geometryItem(i);
    if(const script::Polygon2D* pPolygon = dynamic_cast<const script::Polygon2D*>(pGeometryItem))
      outputPolygon(*pPolygon, os);
  }
}

void outputParams(const script::ParametricProfile& profile, std::ostream& os)
{
  Indent ind1;
  os << Indent::get() << "Params:" << std::endl;
  for (size_t i = 0; i < profile.parametersCount(); ++i)
  {
    auto& parameter = profile.parameter(i);
    Indent ind2;
    os << Indent::get();
    os << "Name: "<< parameter.name();
    os << ", Title: "<< parameter.userName();
    os << ", Type: "<< parameter.type();
    os << ", Value: "<< parameter.value();
    os << std::endl;
  }
}

void outputProfile(const script::ParametricProfile& profile, std::ostream& os)
{
  os << Indent::get() << "Profile description:" << std::endl;
  outputParams(profile, os);
  outputGeometryItems(profile, os);
}