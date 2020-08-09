#pragma once

#include "Path.h"
#include "BrokenTool.h"
#include "FixedTool.h"

class Player
{
public:
  // destructor
  ~Player();

  // draw card
  void addToHand(Card * c) { _hand.push_back(c); }

  // discard cards
  void discardCard(unsigned int i) { _hand.erase(_hand.begin() + i); }

  // rotate card
  void rotateCard(unsigned int i) { _hand[i]->rotate(); }

  // break a tool
  bool breakTool(BrokenTool * b);

  // fix a tool
  BrokenTool * fixTool(FixedTool * f, int broken_tool);

  // print player's hand card
  void printHand();

  // print player's status
  void printStatus();

  // number of cards in hand
  unsigned int handSize() { return _hand.size(); }

  bool hasBrokenTool() { return !_status.empty(); }

  Card * getCard(unsigned int i) { return _hand[i]; }
  Path * getPath(unsigned int i) { return dynamic_cast<Path *>(_hand[i]); }
  BrokenTool * getBrokenTool(unsigned int i) { return dynamic_cast<BrokenTool *>(_hand[i]); }
  FixedTool * getFixedTool(unsigned int i) { return dynamic_cast<FixedTool *>(_hand[i]); }

protected:
private:
  std::vector<Card *> _hand;
  std::vector<BrokenTool *> _status;
};
