#pragma once

#include <iostream>
#include <vector>

#include "Path.h"

#define SLOT_PIXEL_WIDTH 5
#define SLOT_PIXEL_HEIGHT 5

// Forward Declarations
class Slot;

class Slot
{
public:
  Slot();

  std::string operator()(int i, int j);

  void print();

  bool placePath(Path * p);

protected:
private:
  std::vector<std::vector<std::string>> _pixels;
  Path * _path;
};
