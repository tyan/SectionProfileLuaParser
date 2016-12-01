#pragma once

#include <memory>
#include <list>

class IGeometryItem
{
public:
  virtual ~IGeometryItem(){}
};

typedef std::shared_ptr<IGeometryItem> IGeometryItemPtr;
typedef std::list<IGeometryItemPtr> IGeometryItemPtrArray;