#pragma once

#include "Card.h"
#include "BrokenTool.h"

class FixedTool : public Card
{
public:
  // constructor
  FixedTool(Tool tool) : _tool(tool) { draw(); }

  void draw(bool highlight = false) override;

  Tool tool() { return _tool; }

protected:
private:
  // type of broken tool
  Tool _tool;
};
