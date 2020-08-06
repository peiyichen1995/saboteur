#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "Game.h"

Game::Game(unsigned int num)
{
  _board = new Board(5, 9);

  // build connectivity
  Connectivity conn1(false, true, false, false, false, false);
  Connectivity conn2(true, true, false, true, false, false);
  Connectivity conn3(true, true, true, true, true, true);
  Connectivity conn4(false, false, false, true, false, false);
  Connectivity conn5(false, false, false, false, false, true);
  Connectivity conn6(false, false, false, false, false, false);
  Connectivity conn7(true, false, true, false, true, false);
  Connectivity conn8(false, false, false, false, true, false);

  // creat path cards
  createPathHelper(conn1, true, false, true, false, 4);
  createPathHelper(conn2, true, true, true, false, 5);
  createPathHelper(conn3, true, true, true, true, 5);
  createPathHelper(conn4, false, true, true, false, 4);
  createPathHelper(conn5, false, false, true, true, 5);
  createPathHelper(conn6, false, false, true, false, 1);
  createPathHelper(conn6, true, false, true, true, 1);
  createPathHelper(conn6, true, true, true, true, 1);
  createPathHelper(conn6, false, true, true, false, 1);
  createPathHelper(conn6, false, false, true, true, 1);
  createPathHelper(conn6, false, false, false, true, 1);
  createPathHelper(conn7, true, true, false, true, 6);
  createPathHelper(conn8, false, true, false, true, 3);
  createPathHelper(conn6, true, false, true, false, 1);
  createPathHelper(conn6, false, true, false, true, 1);

  // shuffle deck
  std::srand(unsigned(std::time(0)));
  std::random_shuffle(_deck.begin(), _deck.end());

  Player * temp;
  // create players
  for (unsigned int i = 0; i < num; i++)
  {
    temp = new Player();
    _players.push_back(temp);
  }
}

void
Game::createPathHelper(Connectivity conn, bool T, bool R, bool B, bool L, unsigned int num)
{
  Path * temp = nullptr;
  for (unsigned int i = 0; i < num; i++)
  {
    temp = new Path(conn, T, R, B, L);
    _deck.push_back(temp);
  }
}

void
Game::distributeCardToPlayer(unsigned int i)
{
  _players[i]->addToHand(_deck[0]);
  _deck.erase(_deck.begin());
}

void
Game::onGameBegin()
{
  for (unsigned int i = 0; i < 5; i++)
    for (unsigned int j = 0; j < _players.size(); j++)
      distributeCardToPlayer(j);
  _board->print();
}

void
Game::start()
{
  onGameBegin();
}
