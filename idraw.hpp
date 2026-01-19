#ifndef IDRAW_HPP
#define IDRAW_HPP
#include <cstddef>
#include "geom.hpp"
namespace top
{
  struct IDraw //абстрактный класс, для рисования
  {
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };
  void get_points(const IDraw & d, p_t ** pts, size_t & s); //будет расширять массив точек
}
#endif