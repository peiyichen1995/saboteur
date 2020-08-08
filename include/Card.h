#pragma once

#include <vector>
#include <string>

#include "Utils.h"

class Card
{
public:
  Card() : _pixels(pixelType0()) { draw(); }

  virtual ~Card() {}

  std::string operator()(int i, int j) { return _pixels[i][j]; }

  // rotate path
  virtual void rotate() {}

  virtual void draw(bool highlight = false) {}

protected:
  std::vector<std::vector<std::string>> _pixels;

private:
};
