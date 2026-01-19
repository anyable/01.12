#ifndef VSEG_HPP
#define VSEG_HPP
#include "idraw.hpp"
namespace top
{
  struct VSeg : IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t begg;
    size_t lenn;
    VSeg(p_t, size_t);
  };
}
#endif