#ifndef DOT_HPP
#define DOT_HPP
#include "idraw.hpp"
namespace top
{
  struct Dot: IDraw { //точка для рисования
    p_t begin() const override; //центр фигуры
    p_t next(p_t) const override; //следущая точка
    p_t o;
    explicit Dot(p_t dd); //конструктор из точки
    Dot(int x, int y); //конструктор из 2 координат
  };
}
#endif