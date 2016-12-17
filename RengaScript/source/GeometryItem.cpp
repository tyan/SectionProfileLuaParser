#include <GeometryItem.h>
#include "GeometryItemImpl.h"

using namespace script;

GeometryItem::GeometryItem(internal::GeometryItemImpl* pImpl)
  : m_pImpl(pImpl)
{}

GeometryItem::~GeometryItem()
{
  delete m_pImpl;
}

GeometryItem::Type GeometryItem::type() const
{
  return m_pImpl->type();
}
