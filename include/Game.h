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

  // print board and players' hands
  void print();

protected:
private:
  // create path helper
  void createPathHelper(Connectivity conn, bool T, bool R, bool B, bool L, unsigned int num);

  // distribute one card to one player
  void distributeCardToPlayer(unsigned int i);

  // begin the game
  void onGameBegin();

  // begginning of each player's turn
  void onTurnBegin();

  // end of each player's end
  void onTurnEnd();

  // shall we end the game?
  bool endGame() { return false; }

  unsigned int currentPlayer() { return _turn % _players.size(); }

  void printCommands();

  // all path cards
  std::vector<Path *> _deck;

  // game Board
  Board * _board;

  // players
  std::vector<Player *> _players;

  // turn
  unsigned int _turn;

  // number of cards in hand on turn begin
  unsigned int _num_card_on_turn_begin;

  // whether the current player has placed a path
  bool _placed_path;
};
