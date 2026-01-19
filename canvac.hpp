#ifndef CANVAC_HPP
#define CANVAC_HPP
#include "geom.hpp"
#include <iosfwd>
namespace top
{
  char * build_canvas(frame_t f, char fill); //выделяем память под канвас
  void paint_canvas(char * cnv, frame_t fr, p_t p, char fill); //перевести координаты точек в канвас
  void print_canvas(std::ostream & os, const char * cnv, frame_t fr); //вывод канваса, то есть двумерной матрицы
}
#endif