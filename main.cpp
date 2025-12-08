#include <iostream>
namespace top
{


  struct p_t
  {
    int x, y;
  };

  struct IDraw //абстрактный класс
  {
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

  struct Dot: IDraw {
    p_t begin() const override; //центр фигуры
    p_t next(p_t) const override; //следущая точка
    p_t o;
    Dot(int x, int y);
  };

  struct frame_t
  {
    p_t left_bot; //левая граница
    p_t right_top; //правая граница
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

  void make_f(IDraw ** b, size_t k); //выделяем память под фигуры и создаем точки через конструктор
  void get_points(IDraw * b, p_t ** ps, size_t & s); //будет расширять массив точек
  frame_t build_frame(const p_t * ps, size_t s); // макс и мин точки под рамку
  char * build_canvas(frame_t f); //выделяем память под канвас
  void paint_canvas(char * cnv, frame_t r, const p_t * ps, size_t k, char f); //перевести координаты точек в канвас
  void print_canvas(const char * cnv, frame_t fr); //вывод канваса, то есть двумерной матрицы
  void extend(p_t ** pts, size_t s, p_t p);
  size_t points(const IDraw & d, p_t ** res, size_t s);
}
top::Dot::Dot(int x, int y): // конструктор создает центр?
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

void top::get_points(IDraw * b, p_t ** ps, size_t & s)
{
  while (b)
  {
    p_t ** new_ps = new p_t * [++s];
    for (size_t i = 0; i < s - 1; ++i)
    {
      new_ps[i] = ps[i];
    }
    new_ps[s - 1] = &(b -> begin());
    delete [] ps;
    ps = new_ps;
    b++;
  }
}

int main()
{
  using namespace top;
  int err = 0;
  IDraw  * f[3] = {}; // массив фигур
  char * can = nullptr; //канвас на котором будут фигуры
  p_t * p = nullptr; //массив из цетров фигур
  size_t s = 0;
  try
  {
    make_f(f, 3);
    for (size_t i = 0; i < 3; ++i)
    {
      get_points(f[i], &p, s);
    }
    frame_t fo = build_frame(p, s); //рамка
    can = build_canvas(fo); //канвас
    paint_canvas(can, fo, p, s, '*');
    print_canvas(can, fo);
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


size_t top::points(const IDraw & d, p_t ** res, size_t s)
{
  p_t p = d.begin();
  extend(pts, s, p);
  size_t delta = 1;
  while (d.next(p) != d.begin())
  {
    p = d.next(p);
    extend(pts, s + delta, p);
    ++delta;
    // p добавить в массив
  }
  return delta;
}