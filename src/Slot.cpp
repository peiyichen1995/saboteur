#include "Slot.h"
#include "Utils.h"

Slot::Slot() : _path(nullptr) { _pixels = pixelType0(); }

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
    _path = p;
  else
  {
    std::cerr << "this slot already has a path" << std::endl;
    return false;
  }

  return true;
}
