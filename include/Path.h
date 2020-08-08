#pragma once

#include "Card.h"
#include "Connectivity.h"
#include "Utils.h"

class Path : public Card
{
public:
  // constructor
  Path(Connectivity conn, bool T, bool R, bool B, bool L);

  // rotate path
  void rotate() override;

  // draw pixel based on connectivity
  virtual void draw(bool highlight = false) override;

  Connectivity connectivity() { return _conn; }

  bool T() { return _T; }

  bool R() { return _R; }

  bool B() { return _B; }

  bool L() { return _L; }

  virtual bool isStart() { return false; }
  virtual bool isGoal() { return false; }
  virtual bool isTreasure() { return false; }
  virtual bool isStone() { return false; }

protected:
  Connectivity _conn;
  bool _T;
  bool _R;
  bool _B;
  bool _L;

private:
};
