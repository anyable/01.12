#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>
namespace top
{
  struct p_t //точка
  {
    int x, y;
  };
  bool operator==(p_t a, p_t b);
  bool operator!=(p_t a, p_t b);
  struct frame_t
  {
    p_t aa; //левая граница
    p_t bb; //правая граница
  };
  frame_t build_frame(const p_t * ps, size_t s); // макс и мин точки под рамку
  size_t rows(top::frame_t fr);
  size_t cols(top::frame_t fr);
}
#endif