#include "BrokenTool.h"

void
BrokenTool::draw(bool highlight)
{
  _pixels = pixelType0();

  std::string colorPrepend = highlight ? "\033[38;5;10;48;5;250;1m" : "\033[38;5;236;48;5;250;1m";
  std::string colorAppend = "\033[0m";
  if (_tool == Tool::shovel)
  {
    _pixels[1][1] = colorPrepend + "  █  " + colorAppend;
    _pixels[2][1] = colorPrepend + "  █▄▄" + colorAppend;
    _pixels[2][2] = colorPrepend + "▄▄▀" + colorAppend;
    _pixels[2][3] = colorPrepend + "▀▄▄▄ " + colorAppend;
    _pixels[3][1] = colorPrepend + "  █  " + colorAppend;
    _pixels[4][1] = colorPrepend + " ▀▀▀ " + colorAppend;
  }
  else if (_tool == Tool::lantern)
  {
    _pixels[1][1] = colorPrepend + "   ▄▄" + colorAppend;
    _pixels[1][2] = colorPrepend + "▄█▄" + colorAppend;
    _pixels[1][3] = colorPrepend + "▄▄   " + colorAppend;
    _pixels[2][1] = colorPrepend + "    █" + colorAppend;
    _pixels[2][2] = colorPrepend + " § " + colorAppend;
    _pixels[2][3] = colorPrepend + "█    " + colorAppend;
    _pixels[3][1] = colorPrepend + "    █" + colorAppend;
    _pixels[3][2] = colorPrepend + "▄  " + colorAppend;
    _pixels[3][3] = colorPrepend + "█    " + colorAppend;
  }
  else if (_tool == Tool::cart)
  {
    _pixels[1][1] = colorPrepend + "  █  " + colorAppend;
    _pixels[1][3] = colorPrepend + "   █ " + colorAppend;
    _pixels[2][1] = colorPrepend + "  █▄▄" + colorAppend;
    _pixels[2][2] = colorPrepend + "▄▄ " + colorAppend;
    _pixels[2][3] = colorPrepend + "▄▄█  " + colorAppend;
    _pixels[3][1] = colorPrepend + "   ÔÔ" + colorAppend;
    _pixels[3][3] = colorPrepend + "ÔÔ   " + colorAppend;
  }
}
