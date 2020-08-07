#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include <sstream>
#include <fstream>

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

  // create start Path
  _start = new StartingPath(conn3, true, true, true, true);
  _board->placePathInSlot(_start, 2, 0);

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
  _turn = 0;
  for (unsigned int i = 0; i < 5; i++)
    for (unsigned int j = 0; j < _players.size(); j++)
      distributeCardToPlayer(j);
}

void
Game::start()
{
  onGameBegin();
  while (!endGame())
  {
    onTurnBegin();
    onTurnEnd();
  }
}

void
Game::print()
{
  for (unsigned int i = 0; i < 100; i++)
    std::cout << std::endl;

  std::string line;
  std::ifstream out("logo.txt");
  while (std::getline(out, line))
    std::cout << line << std::endl;
  out.close();

  for (unsigned int i = 0; i < 5; i++)
    std::cout << std::endl;

  _board->print();
  for (unsigned int j = 0; j < _players.size(); j++)
  {
    std::cout << std::endl;
    std::cout << "Player " << j << ":" << std::endl;
    _players[j]->printHand();
  }
  printCommands();
}

void
Game::onTurnBegin()
{
  print();
  _num_card_on_turn_begin = _players[currentPlayer()]->handSize();
  _placed_path = false;
  for (std::string line;;)
  {
    std::cout << "Player " << currentPlayer() << " enter command: " && std::getline(std::cin, line);
    std::istringstream user_input(line);
    std::vector<std::string> commands;
    std::string command;
    while (std::getline(user_input, command, ' '))
      commands.push_back(command);
    if (commands[0] == "rotate")
    {
      if (commands.size() != 2)
        printCommands();
      else
      {
        int index = std::stoi(commands[1]);
        _players[currentPlayer()]->rotateCard(index);
        print();
      }
    }
    else if (commands[0] == "path")
    {
      if (commands.size() != 4)
        printCommands();
      else if (_placed_path)
      {
        std::cout << "You can only place one path each turn." << std::endl;
      }
      else
      {
        int index = std::stoi(commands[1]);
        int x = std::stoi(commands[2]);
        int y = std::stoi(commands[3]);
        if (_board->placePathInSlot(_players[currentPlayer()]->getPath(index), x, y))
        {
          _players[currentPlayer()]->discardCard(index);
          _placed_path = true;
          print();
        }
        else
        {
          std::cout << "failed to place path" << std::endl;
        }
      }
    }
    else if (commands[0] == "end")
    {
      if (commands.size() != 1)
        printCommands();
      else if (_players[currentPlayer()]->handSize() == _num_card_on_turn_begin)
        std::cout << "Your should either play a card or discard a card before you end your turn."
                  << std::endl;
      else
        break;
    }
    else if (commands[0] == "discard")
    {
      if (commands.size() != 2)
        printCommands();
      else if (_players[currentPlayer()]->handSize() < _num_card_on_turn_begin)
      {
        std::cout << "You may only discard a card if you haven't played any card in this turn."
                  << std::endl;
      }
      else
      {
        int index = std::stoi(commands[1]);
        _players[currentPlayer()]->discardCard(index);
        break;
      }
    }
    else
      std::cout << "unsupported command" << std::endl;
  }
}

void
Game::onTurnEnd()
{
  while (_players[currentPlayer()]->handSize() < 5)
    if (!_deck.empty())
      distributeCardToPlayer(currentPlayer());
    else
      break;
  _turn++;
}

void
Game::printCommands()
{
  std::cout << std::endl;
  std::cout << dividerBottom() << std::endl;
  std::cout << "Avalable commands:" << std::endl;
  std::cout << "     rotate <card>              ----     rotate a path card" << std::endl;
  std::cout << "     path <card> <x> <y>        ----     place a path card at that location"
            << std::endl;
  std::cout << "     action <card> <player>     ----     place an action card on that player"
            << std::endl;
  std::cout << "     discard <card>             ----     discard that card" << std::endl;
  std::cout << "     end                        ----     end your current turn" << std::endl;
  std::cout << dividerTop() << std::endl;
  std::cout << std::endl;
}
