#include "vseg.hpp"
top::p_t top::VSeg::begin() const
{
  return begg;
}

top::p_t top::VSeg::next(p_t a) const
{
  if (a.y + 1 == begg.y + lenn)
  {
    return begin();
  }
  return {a.x, a.y + 1};
}

top::VSeg::VSeg(p_t a, size_t b):
  begg(a), lenn(b)
  {}
