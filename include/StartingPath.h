#pragma once

#include "Path.h"

class StartingPath;

class StartingPath : public Path
{
public:
  StartingPath(Connectivity conn, bool T, bool R, bool B, bool L) : Path(conn, T, R, B, L)
  {
    _pixels[2][2] = "\033[48;5;236m###\033[0m";
  }

protected:
private:
};
