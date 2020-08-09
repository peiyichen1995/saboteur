#include "FixedTool.h"

void
FixedTool::draw(bool highlight)
{
  _pixels = pixelType0();

  std::string colorPrepend = highlight ? "\033[38;5;10;48;5;250;1m" : "\033[38;5;236;48;5;250;1m";
  std::string colorAppend = "\033[0m";

  _pixels[1][2] = colorPrepend + "fix" + colorAppend;

  if (_tool == Tool::shovel)
  {
    _pixels[2][2] = colorPrepend + "sho" + colorAppend;
    _pixels[2][3] = colorPrepend + "vel  " + colorAppend;
  }
  else if (_tool == Tool::lantern)
  {
    _pixels[2][2] = colorPrepend + "lan" + colorAppend;
    _pixels[2][3] = colorPrepend + "tern " + colorAppend;
  }
  else if (_tool == Tool::cart)
  {
    _pixels[2][2] = colorPrepend + "car" + colorAppend;
    _pixels[2][3] = colorPrepend + "t    " + colorAppend;
  }
  else if (_tool == Tool::lanternandcart)
  {
    _pixels[2][2] = colorPrepend + "lan" + colorAppend;
    _pixels[2][3] = colorPrepend + "tern " + colorAppend;
    _pixels[3][2] = colorPrepend + "car" + colorAppend;
    _pixels[3][3] = colorPrepend + "t    " + colorAppend;
  }
  else if (_tool == Tool::lanternandshovel)
  {
    _pixels[2][2] = colorPrepend + "lan" + colorAppend;
    _pixels[2][3] = colorPrepend + "tern " + colorAppend;
    _pixels[3][2] = colorPrepend + "sho" + colorAppend;
    _pixels[3][3] = colorPrepend + "vel  " + colorAppend;
  }
  else if (_tool == Tool::shovelandcart)
  {
    _pixels[2][2] = colorPrepend + "sho" + colorAppend;
    _pixels[2][3] = colorPrepend + "vel  " + colorAppend;
    _pixels[3][2] = colorPrepend + "car" + colorAppend;
    _pixels[3][3] = colorPrepend + "t    " + colorAppend;
  }
}
