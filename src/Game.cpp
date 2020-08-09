#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include <sstream>
#include <fstream>

#include "Game.h"

Game::Game(unsigned int num)
{
  // std::srand(unsigned(std::time(0)));
  std::srand(0);

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

  // create broken tools
  createBrokenToolHelper(Tool::shovel, 3);
  createBrokenToolHelper(Tool::lantern, 3);
  createBrokenToolHelper(Tool::cart, 3);

  // creat fixed tools
  createFixedToolHelper(Tool::shovel, 2);
  createFixedToolHelper(Tool::lantern, 2);
  createFixedToolHelper(Tool::cart, 2);
  createFixedToolHelper(Tool::lanternandcart, 1);
  createFixedToolHelper(Tool::lanternandshovel, 1);
  createFixedToolHelper(Tool::shovelandcart, 1);

  // shuffle deck
  std::random_shuffle(_deck.begin(), _deck.end());

  // create start Path
  _start = new StartingPath(conn3, true, true, true, true);
  _board->placePathInSlot(_start, 2, 0);

  // place goals
  std::vector<int> secret = {0, 2, 4};
  std::random_shuffle(secret.begin(), secret.end());
  _treasure = new Treasure(conn3, true, true, true, true);
  _board->placePathInSlot(_treasure, secret[0], 8);
  _stone1 = new Stone(conn3, true, true, true, true);
  _board->placePathInSlot(_stone1, secret[1], 8);
  _stone2 = new Stone(conn3, true, true, true, true);
  _board->placePathInSlot(_stone2, secret[2], 8);

  Player * player;
  // create players
  for (unsigned int i = 0; i < num; i++)
  {
    player = new Player();
    _players.push_back(player);
  }
}

Game::~Game()
{
  // clear deck
  for (Card * c : _deck)
    delete c;

  // clear graveyard
  for (Card * c : _graveyard)
    delete c;

  // clear players
  for (Player * p : _players)
    delete p;

  // clear board
  delete _board;
}

void
Game::createPathHelper(Connectivity conn, bool T, bool R, bool B, bool L, unsigned int num)
{
  Card * temp = nullptr;
  for (unsigned int i = 0; i < num; i++)
  {
    temp = new Path(conn, T, R, B, L);
    _deck.push_back(temp);
  }
}

void
Game::createBrokenToolHelper(Tool tool, unsigned int num)
{
  Card * temp = nullptr;
  for (unsigned int i = 0; i < num; i++)
  {
    temp = new BrokenTool(tool);
    _deck.push_back(temp);
  }
}

void
Game::createFixedToolHelper(Tool tool, unsigned int num)
{
  Card * temp = nullptr;
  for (unsigned int i = 0; i < num; i++)
  {
    temp = new FixedTool(tool);
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
  _continue = true;
  _turn = 0;
  for (unsigned int i = 0; i < 5; i++)
    for (unsigned int j = 0; j < _players.size(); j++)
      distributeCardToPlayer(j);
}

void
Game::start()
{
  onGameBegin();
  while (_continue)
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

  for (unsigned int i = 0; i < 2; i++)
    std::cout << std::endl;

  printDeckInfo();

  for (unsigned int i = 0; i < 2; i++)
    std::cout << std::endl;

  _board->print();
  for (unsigned int j = 0; j < _players.size(); j++)
  {
    std::cout << std::endl;
    std::cout << "Player " << j << ":" << std::endl;
    _players[j]->printStatus();
    _players[j]->printHand();
  }

  printCommands();
}

void
Game::onTurnBegin()
{
  print();
  _board->resetColor();
  _num_card_on_turn_begin = _players[currentPlayer()]->handSize();
  for (std::string line;;)
  {
    std::cout << "Player " << currentPlayer() << " enter command: " && std::getline(std::cin, line);
    std::istringstream user_input(line);
    std::vector<std::string> commands;
    std::string command;
    while (std::getline(user_input, command, ' '))
      commands.push_back(command);
    if (commands[0] == "r")
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
    else if (commands[0] == "p")
    {
      if (commands.size() != 4)
        printCommands();
      else
      {
        if (_players[currentPlayer()]->hasBrokenTool())
          std::cout << "You have a broken tool!" << std::endl;
        else
        {
          int index = std::stoi(commands[1]);
          int x = std::stoi(commands[2]);
          int y = std::stoi(commands[3]);
          if (_board->placePathInSlot(_players[currentPlayer()]->getPath(index), x, y))
          {
            _players[currentPlayer()]->discardCard(index);
            break;
          }
          else
            std::cout << "failed to place path" << std::endl;
        }
      }
    }
    else if (commands[0] == "b")
    {
      if (commands.size() != 3)
        printCommands();
      else
      {
        int card = std::stoi(commands[1]);
        int player = std::stoi(commands[2]);
        if (_players[player]->breakTool(_players[currentPlayer()]->getBrokenTool(card)))
        {
          _players[currentPlayer()]->discardCard(card);
          break;
        }
        else
          std::cout << "failed to break the tool" << std::endl;
      }
    }
    else if (commands[0] == "f")
    {
      if (commands.size() != 4)
        printCommands();
      else
      {
        int card = std::stoi(commands[1]);
        int player = std::stoi(commands[2]);
        int broken_tool = std::stoi(commands[3]);
        BrokenTool * fixed_broken_tool =
            _players[player]->fixTool(_players[currentPlayer()]->getFixedTool(card), broken_tool);
        if (fixed_broken_tool)
        {
          _graveyard.push_back(_players[currentPlayer()]->getCard(card));
          _graveyard.push_back(fixed_broken_tool);
          _players[currentPlayer()]->discardCard(card);
          break;
        }
        else
          std::cout << "failed to fix the tool" << std::endl;
      }
    }
    else if (commands[0] == "d")
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
        _graveyard.push_back(_players[currentPlayer()]->getCard(index));
        _players[currentPlayer()]->discardCard(index);
        break;
      }
    }
    else if (commands[0] == "quit")
    {
      if (commands.size() != 1)
        printCommands();
      else
      {
        _continue = false;
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
  if (!_continue)
    return;

  while (_players[currentPlayer()]->handSize() < 5)
    if (!_deck.empty())
      distributeCardToPlayer(currentPlayer());
    else
      break;

  _turn++;
}

void
Game::printDeckInfo()
{
  std::cout << "Deck: " << _deck.size() << "             Graveyard: " << _graveyard.size()
            << std::endl;
}

void
Game::printCommands()
{
  std::cout << std::endl;
  std::cout << dividerBottom() << std::endl;
  std::cout << "Avalable commands:" << std::endl;
  std::cout << "     r <card>                    ----     rotate a path card" << std::endl;
  std::cout << "     p <card> <x> <y>            ----     place a path card at that location"
            << std::endl;
  std::cout << "     b <card> <player>           ----     break a player's tool" << std::endl;
  std::cout << "     f <card> <player> <tool>    ----     fix a player's certain broken tool"
            << std::endl;
  std::cout << "     d <card>                    ----     discard that card" << std::endl;
  std::cout << "     q                           ----     quit game" << std::endl;
  std::cout << dividerTop() << std::endl;
  std::cout << std::endl;
}
