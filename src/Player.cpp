#include "Player.h"
#include "Slot.h"

Player::~Player()
{
  for (Card * c : _hand)
    delete c;
  for (Card * c : _status)
    delete c;
}

bool
Player::breakTool(BrokenTool * b)
{
  for (BrokenTool * c : _status)
    if (c->tool() == b->tool())
      return false;
  _status.push_back(b);
  return true;
}

BrokenTool *
Player::fixTool(FixedTool * f, int broken_tool)
{
  std::cout << "broken_tool = " << broken_tool << std::endl;
  std::cout << "_status.size() = " << _status.size() << std::endl;
  if ((unsigned int)broken_tool >= _status.size())
    return nullptr;

  BrokenTool * fixed_broken_tool = nullptr;

  if (f->tool() == Tool::lantern || f->tool() == Tool::lanternandshovel ||
      f->tool() == Tool::lanternandcart)
    if (_status[broken_tool]->tool() == Tool::lantern)
      fixed_broken_tool = _status[broken_tool];

  if (f->tool() == Tool::shovel || f->tool() == Tool::lanternandshovel ||
      f->tool() == Tool::shovelandcart)
    if (_status[broken_tool]->tool() == Tool::shovel)
      fixed_broken_tool = _status[broken_tool];

  if (f->tool() == Tool::cart || f->tool() == Tool::shovelandcart ||
      f->tool() == Tool::lanternandcart)
    if (_status[broken_tool]->tool() == Tool::cart)
      fixed_broken_tool = _status[broken_tool];

  if (fixed_broken_tool)
    _status.erase(_status.begin() + broken_tool);

  return fixed_broken_tool;
}

void
Player::printHand()
{
  for (unsigned int h = 0; h < SLOT_PIXEL_HEIGHT; h++)
  {
    for (unsigned int j = 0; j < _hand.size(); j++)
    {
      for (unsigned int w = 0; w < SLOT_PIXEL_WIDTH; w++)
        std::cout << (*_hand[j])(h, w);
      std::cout << "   ";
    }
    std::cout << std::endl;
  }
}

void
Player::printStatus()
{
  if (_status.empty())
    return;
  for (BrokenTool * b : _status)
  {
    if (b->tool() == Tool::shovel)
      std::cout << "[BROKEN SHOVEL]";
    if (b->tool() == Tool::lantern)
      std::cout << "[BROKEN LANTERN]";
    if (b->tool() == Tool::cart)
      std::cout << "[BROKEN CART]";
  }
  std::cout << "   You may not place any path!" << std::endl;
}
