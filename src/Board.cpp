#include "Board.h"

Board::Board(unsigned int row, unsigned int col) : _row(row), _col(col)
{
  _slots.resize(row);
  for (unsigned int i = 0; i < row; i++)
  {
    _slots[i].resize(col);
    for (unsigned int j = 0; j < col; j++)
    {
      _slots[i][j] = new Slot();
    }
  }
}

void
Board::print()
{
  for (unsigned int i = 0; i < _row; i++)
  {
    for (unsigned int h = 0; h < SLOT_PIXEL_HEIGHT - 1; h++)
    {
      for (unsigned int j = 0; j < _col; j++)
      {
        for (unsigned int w = 0; w < SLOT_PIXEL_WIDTH - 1; w++)
          std::cout << (*_slots[i][j])(h, w);
        if (j == _col - 1)
          std::cout << (*_slots[i][j])(h, SLOT_PIXEL_WIDTH - 1);
      }
      std::cout << std::endl;
    }
    if (i == _row - 1)
    {
      for (unsigned int j = 0; j < _col; j++)
      {
        for (unsigned int w = 0; w < SLOT_PIXEL_WIDTH - 1; w++)
          std::cout << (*_slots[i][j])(SLOT_PIXEL_HEIGHT - 1, w);
        if (j == _col - 1)
          std::cout << (*_slots[i][j])(SLOT_PIXEL_HEIGHT - 1, SLOT_PIXEL_WIDTH - 1);
      }
      std::cout << std::endl;
    }
  }
}

bool
Board::placePathInSlot(Path * p, int i, int j)
{
  return _slots[i][j]->placePath(p);
}
