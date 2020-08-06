#pragma once

#include "Path.h"

class Player
{
public:
  // draw card
  void addToHand(Card * c) { _hand.push_back(c); }

  // discard cards
  void discardCard(unsigned int i) { _hand.erase(_hand.begin() + i); }

protected:
private:
  std::vector<Card *> _hand;
};
