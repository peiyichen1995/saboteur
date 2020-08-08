#pragma once

#include "Path.h"

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

  // print player's hand card
  void printHand();

  // number of cards in hand
  unsigned int handSize() { return _hand.size(); }

  Card * getCard(unsigned int i) { return _hand[i]; }
  Path * getPath(unsigned int i) { return dynamic_cast<Path *>(_hand[i]); }

protected:
private:
  std::vector<Card *> _hand;
};
