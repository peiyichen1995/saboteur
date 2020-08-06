#pragma once

#include "Board.h"
#include "Player.h"

class Game;

class Game
{
public:
  // constructor
  Game(unsigned int num);

  // start Game
  void start();

protected:
private:
  // create path helper
  void createPathHelper(Connectivity conn, bool T, bool R, bool B, bool L, unsigned int num);

  // distribute one card to one player
  void distributeCardToPlayer(unsigned int i);

  // begin the game
  void onGameBegin();

  // all path cards
  std::vector<Path *> _deck;

  // game Board
  Board * _board;

  std::vector<Player *> _players;
};
