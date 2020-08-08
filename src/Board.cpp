#include "Board.h"

Board::Board(unsigned int row, unsigned int col) : _row(row), _col(col)
{
  _slots.resize(row);
  for (unsigned int i = 0; i < row; i++)
  {
    _slots[i].resize(col);
    for (unsigned int j = 0; j < col; j++)
      _slots[i][j] = new Slot();
  }

  defineNeighbors();
}

Board::~Board()
{
  for (unsigned int i = 0; i < _row; i++)
    for (unsigned int j = 0; j < _col; j++)
      delete _slots[i][j];
}

void
Board::print()
{
  std::cout << "      ";
  for (unsigned int j = 0; j < _col; j++)
    for (unsigned int w = 0; w < SLOT_PIXEL_WIDTH; w++)
      if (w == (SLOT_PIXEL_WIDTH - 1) / 2)
        std::cout << "    " << j << "     ";
      else
        std::cout << " ";
  std::cout << std::endl;
  std::cout << std::endl;

  for (unsigned int i = 0; i < _row; i++)
  {
    for (unsigned int h = 0; h < SLOT_PIXEL_HEIGHT - 1; h++)
    {
      if (h == (SLOT_PIXEL_HEIGHT - 1) / 2)
        std::cout << "  " << i << "  ";
      else
        std::cout << "     ";
      for (unsigned int j = 0; j < _col; j++)
      {
        for (unsigned int w = 0; w < SLOT_PIXEL_WIDTH - 1; w++)
        {
          if (i > 0 && h == 0)
          {
            std::string upper = (*_slots[i - 1][j])(SLOT_PIXEL_HEIGHT - 1, w);
            std::string lower = (*_slots[i][j])(0, w);
            std::cout << std::min(upper, lower);
          }
          else if (j > 0 && w == 0)
          {
            std::string left = (*_slots[i][j - 1])(h, SLOT_PIXEL_WIDTH - 1);
            std::string right = (*_slots[i][j])(h, 0);
            std::cout << std::min(left, right);
          }
          else
            std::cout << (*_slots[i][j])(h, w);
        }
        if (j == _col - 1)
          std::cout << (*_slots[i][j])(h, SLOT_PIXEL_WIDTH - 1);
      }
      std::cout << std::endl;
    }
  }
  std::cout << "     ";
  for (unsigned int j = 0; j < _col; j++)
  {
    for (unsigned int w = 0; w < SLOT_PIXEL_WIDTH - 1; w++)
      std::cout << (*_slots[_row - 1][j])(SLOT_PIXEL_HEIGHT - 1, w);
    if (j == _col - 1)
      std::cout << (*_slots[_row - 1][j])(SLOT_PIXEL_HEIGHT - 1, SLOT_PIXEL_WIDTH - 1);
  }
  std::cout << std::endl;
}

bool
Board::placePathInSlot(Path * p, int i, int j)
{
  return _slots[i][j]->placePath(p);
}

void
Board::defineNeighbors()
{
  for (unsigned int i = 0; i < _row; i++)
    for (unsigned int j = 0; j < _col; j++)
    {
      if (i >= 1)
        _slots[i][j]->addT(_slots[i - 1][j]);
      if (i + 1 < _row)
        _slots[i][j]->addB(_slots[i + 1][j]);
      if (j >= 1)
        _slots[i][j]->addL(_slots[i][j - 1]);
      if (j + 1 < _col)
        _slots[i][j]->addR(_slots[i][j + 1]);
    }
}

void
Board::resetColor()
{
  for (unsigned int i = 0; i < _row; i++)
    for (unsigned int j = 0; j < _col; j++)
      _slots[i][j]->resetColor();
}
