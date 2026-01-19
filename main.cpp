#include <iostream>
#include "geom.hpp"
#include "idraw.hpp"
#include "dot.hpp"
#include "vseg.hpp"
#include "canvac.hpp"
namespace top
{
  struct HSeg : IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t beg;
    size_t len;
    HSeg(p_t, size_t);
  };

  struct DSeg : IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t beggg;
    size_t lennn;
    DSeg(p_t, size_t);
  };

  struct Rectangle : IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t beg_;
    int widht_;
    int hight_;
    Rectangle(p_t, int, int);
  };

  struct Square : Rectangle
  {
    Square(p_t, int);
  };

  void make_f(IDraw ** b, size_t k); //выделяем память под фигуры и создаем точки через конструктор, то есть центры
}

top::Square::Square(p_t begin, int len):
  Rectangle(begin, len, len)
  {}

top::p_t top::Rectangle::next(p_t p) const
{
  p_t upLeft = {beg_.x, beg_.y + hight_ - 1};
  p_t downLeft = beg_;
  p_t upRight = {beg_.x + widht_ - 1, beg_.y + hight_ - 1};
  p_t downRight = {beg_.x + widht_ - 1, beg_.y};
  if (p.x - 1 == downLeft.x && p.y == downLeft.y)
  {
    return begin();
  }
  else if (p.x == upLeft.x && p.y < upLeft.y)
  {
    return {p.x, p.y + 1};
  }
  else if ((p == upLeft) || (p.y == upRight.y && p.x < upRight.x))
  {
    return {p.x + 1, p.y};
  }
  else if ((p == upRight) || (p.x == downRight.x && p.y > downRight.y))
  {
    return {p.x, p.y - 1};
  }
  return {p.x - 1, p.y};
}

top::p_t top::Rectangle::begin() const
{
  return beg_;
}

top::Rectangle::Rectangle(p_t begin, int weight, int hight):
  IDraw(), beg_(begin), widht_(weight), hight_(hight)
  {
    if (weight <= 0 || hight <= 0)
    {
      throw std::logic_error("");
    }
  }

top::DSeg::DSeg(p_t a, size_t b):
  beggg(a), lennn(b)
  {}

top::p_t top::DSeg::begin() const
{
  return beggg;
}

top::p_t top::DSeg::next(p_t a) const
{
  if (a.x + 1 == beggg.x + lennn && a.y + 1 == beggg.y + lennn)
  {
    return begin();
  }
  return {a.x + 1, a.y + 1};
}

top::HSeg::HSeg(p_t a, size_t b):
  beg(a), len(b)
  {}

top::p_t top::HSeg::begin() const
{
  return beg;
}

top::p_t top::HSeg::next(p_t a) const
{
  if (a.x + 1 == beg.x + len)
  {
    return begin();
  }
  return {a.x + 1, a.y};
}

void top::make_f(IDraw ** b, size_t k)
{
  b[0] = new HSeg({0, 0}, 4);
  b[1] = new Square({13, -7}, 8);
  b[2] = new Rectangle({-12, 3}, 9, 12);
}

int main()
{
  using namespace top;
  int err = 0; //индиф ошибки
  IDraw  * f[3] = {}; // массив фигур
  char * can = nullptr; //канвас на котором будут фигуры
  p_t * p = nullptr; //массив из цетров фигур
  size_t s = 0;
  try
  {
    make_f(f, 3);
    for (size_t i = 0; i < 3; ++i)
    {
      get_points(*(f[i]), &p, s);
    }
    frame_t fo = build_frame(p, s); //рамка
    can = build_canvas(fo, '.'); //канвас
    for (size_t i = 0; i < s; ++i)
    {
      paint_canvas(can, fo, p[i], '@');
    }
    print_canvas(std::cout, can, fo);
  }
  catch (...)
  {
    err = 1;
  }
  delete f[0];
  delete f[1];
  delete f[2];
  delete [] p;
  delete [] can;
  return err;
}
