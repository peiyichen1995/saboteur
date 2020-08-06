#pragma once

#include "Card.h"
#include "Connectivity.h"
#include "Utils.h"

class Path : public Card
{
public:
  // constructor
  Path(Connectivity conn, bool T, bool R, bool B, bool L);

  std::string operator()(int i, int j);

  // rotate path
  void rotate();

  // draw pixel based on connectivity
  void draw();

protected:
private:
  Connectivity _conn;
  bool _T;
  bool _R;
  bool _B;
  bool _L;
  std::vector<std::vector<std::string>> _pixels;
};
