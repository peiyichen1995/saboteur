#pragma once

#include "Path.h"

class StartingPath;

class StartingPath : public Path
{
public:
  StartingPath(Connectivity conn, bool T, bool R, bool B, bool L) : Path(conn, T, R, B, L)
  {
    draw();
  }

  virtual bool isStart() override { return true; }

  virtual void draw(bool highlight = false) override;

protected:
private:
};
