#pragma once

#include <vector>
#include <string>

#include "Utils.h"

class Card
{
public:
  Card() : _pixels(pixelType0()) {}

  std::string operator()(int i, int j) { return _pixels[i][j]; }

  // rotate path
  virtual void rotate() {}

protected:
  std::vector<std::vector<std::string>> _pixels;

private:
};
