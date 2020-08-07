#pragma once

#include <iostream>
#include <vector>

#include "StartingPath.h"

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

  // add neighbors
  void addT(Slot * s) { _T = s; }

  void addB(Slot * s) { _B = s; }

  void addR(Slot * s) { _R = s; }

  void addL(Slot * s) { _L = s; }

  // return slots
  Slot * const T() { return _T; }

  Slot * const B() { return _B; }

  Slot * const R() { return _R; }

  Slot * const L() { return _L; }

protected:
private:
  // pixels
  std::vector<std::vector<std::string>> _pixels;
  // path in slot
  Path * _path;
  // top neighbour
  Slot * _T;
  // bottom neighbour
  Slot * _B;
  // right neighbour
  Slot * _R;
  // left neighbour
  Slot * _L;
};
