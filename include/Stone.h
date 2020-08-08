#pragma once

#include "Path.h"

class Stone;

class Stone : public Path
{
public:
  Stone(Connectivity conn, bool T, bool R, bool B, bool L) : Path(conn, T, R, B, L) { draw(); }

  bool isGoal() override { return true; }
  bool isStone() override { return true; }

  virtual void draw(bool highlight = false) override;

protected:
private:
};
