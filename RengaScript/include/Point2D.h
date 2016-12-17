#pragma once
#include "RengaScript.h"

namespace script
{
  struct RENGA_SCRIPT_EXTERNAL Point2D
  {
    Point2D()
      : x(0.), y(0.)
    {
    }

    Point2D(double x, double y)
      : x(x), y(y)
    {
    }

    double x;
    double y;
  };
}