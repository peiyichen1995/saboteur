#pragma once

#include "Board.h"
#include "Player.h"
#include "FixedTool.h"

class Game;

class Game
{
public:
  // constructor
  Game(unsigned int num);

  // destructor
  ~Game();

  // start Game
  void start();

  // print board and players' hands
  void print();

protected:
private:
  // create path helper
  void createPathHelper(Connectivity conn, bool T, bool R, bool B, bool L, unsigned int num);

  // create broken tool helper
  void createBrokenToolHelper(Tool tool, unsigned int num);

  // create fixed tool helper
  void createFixedToolHelper(Tool tool, unsigned int num);

  // distribute one card to one player
  void distributeCardToPlayer(unsigned int i);

  // begin the game
  void onGameBegin();

  // begginning of each player's turn
  void onTurnBegin();

  // end of each player's end
  void onTurnEnd();

  unsigned int currentPlayer() { return _turn % _players.size(); }

  void printDeckInfo();

  void printCommands();

  // shall we continue?
  bool _continue;

  // all path cards
  std::vector<Card *> _deck;

  // all discarded cards
  std::vector<Card *> _graveyard;

  // game Board
  Board * _board;

  // players
  std::vector<Player *> _players;

  // turn
  unsigned int _turn;

  // number of cards in hand on turn begin
  unsigned int _num_card_on_turn_begin;

  // start Path
  Path * _start;

  // goals
  Path * _treasure;
  Path * _stone1;
  Path * _stone2;
};
