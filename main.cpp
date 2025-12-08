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

  struct VSeg
  {
    int x;
    int up_y;
    int down_y;
  };

  struct HSeg
  {
    int y;
    int left_x;
    int right_x;
  };

  void make_f(IDraw ** b, size_t k); //выделяем память под фигуры и создаем точки через конструктор, то есть центры

  void get_points(const IDraw & d, p_t ** pts, size_t & s); //будет расширять массив точек

  frame_t build_frame(const p_t * ps, size_t s); // макс и мин точки под рамку

  char * build_canvas(frame_t f, char fill); //выделяем память под канвас

  void paint_canvas(char * cnv, frame_t fr, p_t p, char fill); //перевести координаты точек в канвас

  void print_canvas(std::ostream & os, const char * cnv, frame_t fr); //вывод канваса, то есть двумерной матрицы

  void extend(p_t ** pts, size_t s, p_t p); //расширение массива 
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
  b[0] = new Dot(0, 0);
  b[1] = new Dot(-1, -5);
  b[2] = new Dot(7, 7);
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
  p_t p = d.begin(); //центр фигуры
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
    can = build_canvas(fo, '*'); //канвас
    for (size_t i = 0; i < s; ++i)
    {
      paint_canvas(can, fo, p[i], '.');
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








