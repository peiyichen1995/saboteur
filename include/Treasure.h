#pragma once

#include "Path.h"

class Treasure;

class Treasure : public Path
{
public:
  Treasure(Connectivity conn, bool T, bool R, bool B, bool L) : Path(conn, T, R, B, L) { draw(); }

  bool isGoal() override { return true; }
  bool isTreasure() override { return true; }

  virtual void draw(bool highlight = false) override;

protected:
private:
};
