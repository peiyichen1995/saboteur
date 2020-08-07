#include "Utils.h"
#include "Slot.h"

std::vector<std::vector<std::string>>
pixelType0()
{
  std::vector<std::vector<std::string>> pixels;
  pixels.resize(SLOT_PIXEL_HEIGHT);
  pixels[0] = {"╬", "══", "═╬═", "══", "╬"};
  pixels[1] = {"║", "  ", "   ", "  ", "║"};
  pixels[2] = {"╬", "  ", "   ", "  ", "╬"};
  pixels[3] = {"║", "  ", "   ", "  ", "║"};
  pixels[4] = {"╬", "══", "═╬═", "══", "╬"};
  return pixels;
}

std::string
dividerTop()
{
  return "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░";
}

std::string
dividerBottom()
{
  return "░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░";
}
