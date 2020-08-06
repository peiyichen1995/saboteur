#pragma once

#include <vector>
#include "Slot.h"

class Board;

class Board
{
public:
  // constructor of Board
  Board(unsigned int row, unsigned int col);

  void print();

  bool placePathInSlot(Path * p, int i, int j);

protected:
private:
  unsigned int _row;
  unsigned int _col;
  // list of pointer to slots
  std::vector<std::vector<Slot *>> _slots;
};
