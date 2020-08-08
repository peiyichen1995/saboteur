#pragma once

#include <vector>
#include "Slot.h"

class Board;

class Board
{
public:
  Board(unsigned int row, unsigned int col);

  ~Board();

  void print();

  bool placePathInSlot(Path * p, int i, int j);

  // define neighbors for each slot
  void defineNeighbors();

  void resetColor();

protected:
private:
  unsigned int _row;
  unsigned int _col;
  // list of pointer to slots
  std::vector<std::vector<Slot *>> _slots;
};
