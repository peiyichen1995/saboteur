#pragma once

#include "Card.h"

class Map : public Card
{
public:
  // constructor
  Map(int treasure) : _treasure(treasure) { draw(); }

  void draw(bool highlight = false) override;
  bool reveal(int goal) { return goal == _treasure; }

protected:
private:
  int _treasure;
};
