#include "dot.hpp"
#include <stdexcept>
top::Dot::Dot(int x, int y): // конструктор создает центр
    IDraw(),
    o{x, y}
    {}

top::p_t top::Dot::begin() const
{
  return o;
}

top::p_t top::Dot::next(p_t) const
{
  return begin();
}

top::Dot::Dot(p_t dd):
 IDraw(),
 o{dd}
{}