#pragma once

#include "Card.h"

enum Tool
{
  lantern,
  cart,
  shovel,
  lanternandcart,
  lanternandshovel,
  shovelandcart
};

class BrokenTool : public Card
{
public:
  // constructor
  BrokenTool(Tool tool) : _tool(tool) { draw(); }

  void draw(bool highlight = false) override;

  Tool tool() { return _tool; }

protected:
private:
  // type of broken tool
  Tool _tool;
};
