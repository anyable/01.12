#include <iostream>
namespace top
{
  struct p_t //точка
  {
    int x, y;
  };

  struct IDraw //абстрактный класс, для рисования
  {
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }

  struct Dot: IDraw { //точка для рисования
    p_t begin() const override; //центр фигуры
    p_t next(p_t) const override; //следущая точка
    p_t o;
    explicit Dot(p_t dd); //конструктор из точки
    Dot(int x, int y); //конструктор из 2 координат
  };

  struct frame_t
  {
    p_t aa; //левая граница
    p_t bb; //правая граница
  };

  struct VSeg : IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t begg;
    size_t lenn;
    VSeg(p_t, size_t);
  };

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
    Rectangle(p_t, size_t, size_t);
  };

  void make_f(IDraw ** b, size_t k); //выделяем память под фигуры и создаем точки через конструктор, то есть центры
  void get_points(const IDraw & d, p_t ** pts, size_t & s); //будет расширять массив точек
  frame_t build_frame(const p_t * ps, size_t s); // макс и мин точки под рамку
  char * build_canvas(frame_t f, char fill); //выделяем память под канвас
  void paint_canvas(char * cnv, frame_t fr, p_t p, char fill); //перевести координаты точек в канвас
  void print_canvas(std::ostream & os, const char * cnv, frame_t fr); //вывод канваса, то есть двумерной матрицы
  void extend(p_t ** pts, size_t s, p_t p); //расширение массива
}

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

top::Rectangle::Rectangle(p_t begin, size_t weight, size_t hight):
  IDraw(), beg_(begin), widht_(weight), hight_(hight)
  {}

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

void top::make_f(IDraw ** b, size_t k)
{
  b[0] = new HSeg({0, 0}, 4);
  b[1] = new VSeg({5, -3}, 6);
  b[2] = new Rectangle({-12, 3}, 9, 12);
}

void top::extend(p_t ** pts, size_t s, p_t p)
{
  p_t * res = new p_t[s + 1];
  for (size_t i = 0; i < s; ++ i)
  {
    res[i] = (*pts)[i];
  }
  res[s] = p;
  delete [] * pts;
  *pts = res;
}

void top::get_points(const IDraw & d, p_t ** pts, size_t & s)
{
  p_t p = d.begin(); //начало
  extend(pts, s, p);
  size_t delta = 1;
  while (d.next(p) != d.begin())
  {
    p = d.next(p);
    extend(pts, s + delta, p);
    ++delta;
    // p добавить в массив
  }
  s += delta;
}

size_t rows(top::frame_t fr)
{
  return (fr.bb.y - fr.aa.y + 1);
}

size_t cols(top::frame_t fr)
{
  return (fr.bb.x - fr.aa.x + 1);
}

top::frame_t top::build_frame(const p_t * pts, size_t s)
{
  if (!s)
  {
    throw std::logic_error("bad size");
  }
  int minx = pts[0].x, maxx = minx;
  int miny = pts[0].y, maxy = miny;
  for (size_t i = 1; i < s; ++i)
  {
    minx = std::min(minx, pts[i].x);
    maxx = std::max(maxx, pts[i].x);
    miny = std::min(miny, pts[i].y);
    maxy = std::max(maxy, pts[i].y);
  }
  p_t aa{minx, miny};
  p_t bb{maxx, maxy};
  return {aa, bb};
}

char * top::build_canvas(frame_t fr, char fill)
{
  char * cnv = new char[rows(fr) * cols(fr)];
  for (size_t i = 0; i < rows(fr) * cols(fr); ++i)
  {
    cnv[i] = fill;
  }
  return cnv;
}

void top::paint_canvas(char * cnv, frame_t fr, p_t p, char fill)
{
  int dx = p.x - fr.aa.x;
  int dy = fr.bb.y - p.y;
  cnv[dy * cols(fr) + dx] = fill;
}

void top::print_canvas(std::ostream & os, const char * cnv, frame_t fr)
{
  for (size_t i = 0; i < rows(fr); ++i)
  {
    for (size_t j = 0; j < cols(fr); ++j)
    {
      os << cnv[i * cols(fr) + j];
    }
    os << '\n';
  }
}

top::Dot::Dot(p_t dd):
 IDraw(),
 o{dd}
{}

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
