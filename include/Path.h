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
  void draw();

protected:
private:
  Connectivity _conn;
  bool _T;
  bool _R;
  bool _B;
  bool _L;
};
