#include "Slot.h"
#include "Utils.h"

Slot::Slot() : _path(nullptr), _T(nullptr), _B(nullptr), _R(nullptr), _L(nullptr)
{
  _pixels = pixelType0();
}

void
Slot::print()
{
  for (unsigned int i = 0; i < SLOT_PIXEL_HEIGHT; i++)
  {
    for (unsigned int j = 0; j < SLOT_PIXEL_WIDTH; j++)
      std::cout << _pixels[i][j];
    std::cout << std::endl;
  }
}

std::string
Slot::operator()(int i, int j)
{
  if (!_path)
    return _pixels[i][j];
  else
    return (*_path)(i, j);
}

bool
Slot::placePath(Path * p)
{
  if (!_path)
  {
    if ((_T && _T->_path) && (_T->_path->B() != p->T()))
    {
      std::cerr << "illegal top neighbor" << std::endl;
      return false;
    }
    if ((_R && _R->_path) && (_R->_path->L() != p->R()))
    {
      std::cerr << "illegal right neighbor" << std::endl;
      return false;
    }
    if ((_B && _B->_path) && (_B->_path->T() != p->B()))
    {
      std::cerr << "illegal bottom neighbor" << std::endl;
      return false;
    }
    if ((_L && _L->_path) && (_L->_path->R() != p->L()))
    {
      std::cerr << "illegal left neighbor" << std::endl;
      return false;
    }
  }
  else
  {
    std::cerr << "this slot already has a path" << std::endl;
    return false;
  }

  _path = p;

  return true;
}
