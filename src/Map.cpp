#include "Map.h"

void
Map::draw(bool highlight)
{
  _pixels = pixelType0();

  std::string colorPrepend = highlight ? "\033[38;5;10;48;5;250;1m" : "\033[38;5;236;48;5;250;1m";
  std::string colorAppend = "\033[0m";

  _pixels[2][2] = colorPrepend + "MAP" + colorAppend;
}
