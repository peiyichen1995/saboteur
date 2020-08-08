#include "Slot.h"
#include "Utils.h"
#include <algorithm>

Slot::Slot() : _path(nullptr), _T(nullptr), _B(nullptr), _R(nullptr), _L(nullptr)
{
  _pixels = pixelType0();
}

void
Slot::print()
{
  for (unsigned int i = 0; i < SLOT_PIXEL_HEIGHT; i++)
  {
    for (unsigned int j = 0; j < SLOT_PIXEL_WIDTH; j++)
      std::cout << _pixels[i][j];
    std::cout << std::endl;
  }
}

std::string
Slot::operator()(int i, int j)
{
  if (!_path)
    return _pixels[i][j];
  else
    return (*_path)(i, j);
}

bool
Slot::placePath(Path * p)
{
  if (p->isStart() || p->isGoal())
  {
  }
  else
  {
    if (_path)
    {
      std::cout << "this slot already has a path" << std::endl;
      return false;
    }
    else
    {
      bool isolated = true;

      if ((_T && _T->_path && !_T->_path->isGoal()) && (_T->_path->B() != p->T()))
      {
        std::cout << "illegal top neighbor" << std::endl;
        return false;
      }
      else
        isolated = false;

      if ((_R && _R->_path && !_R->_path->isGoal()) && (_R->_path->L() != p->R()))
      {
        std::cout << "illegal right neighbor" << std::endl;
        return false;
      }
      else
        isolated = false;

      if ((_B && _B->_path && !_B->_path->isGoal()) && (_B->_path->T() != p->B()))
      {
        std::cout << "illegal bottom neighbor" << std::endl;
        return false;
      }
      else
        isolated = false;

      if ((_L && _L->_path && !_L->_path->isGoal()) && (_L->_path->R() != p->L()))
      {
        std::cout << "illegal left neighbor" << std::endl;
        return false;
      }
      else
        isolated = false;

      if (isolated)
      {
        std::cout << "a floating path" << std::endl;
        return false;
      }
    }
  }

  _path = p;

  // get connected path to start
  std::vector<Slot *> final_path;
  if (isConnectedToStart(final_path))
  {
    std::cout << "found the way all the way to start consisting of " << final_path.size()
              << " path cards." << std::endl;
    for (Slot * s : final_path)
      s->_path->draw(true);
  }
  else
  {
    std::cout << "no way to start could be found." << std::endl;
  }

  final_path.clear();
  if (_T && _T->_path && _T->_path->isGoal() && _T->isConnectedToStart(final_path))
    for (Slot * s : final_path)
      s->_path->draw(true);

  final_path.clear();
  if (_B && _B->_path && _B->_path->isGoal() && _B->isConnectedToStart(final_path))
    for (Slot * s : final_path)
      s->_path->draw(true);

  final_path.clear();
  if (_R && _R->_path && _R->_path->isGoal() && _R->isConnectedToStart(final_path))
    for (Slot * s : final_path)
      s->_path->draw(true);

  return true;
}

bool
Slot::isConnectedToStart(std::vector<Slot *> & final_path)
{
  std::vector<Slot *> visited;

  visited.clear();
  final_path.clear();
  if (_path->T() && isConnectedToStartThrough(_T, this, visited, final_path))
  {
    final_path.push_back(_T);
    final_path.push_back(this);
    return true;
  }

  visited.clear();
  final_path.clear();
  if (_path->R() && isConnectedToStartThrough(_R, this, visited, final_path))
  {
    final_path.push_back(_R);
    final_path.push_back(this);
    return true;
  }

  visited.clear();
  final_path.clear();
  if (_path->B() && isConnectedToStartThrough(_B, this, visited, final_path))
  {
    final_path.push_back(_B);
    final_path.push_back(this);
    return true;
  }

  visited.clear();
  final_path.clear();
  if (_path->L() && isConnectedToStartThrough(_L, this, visited, final_path))
  {
    final_path.push_back(_L);
    final_path.push_back(this);
    return true;
  }

  return false;
}

bool
Slot::isConnectedToStartThrough(Slot * current,
                                Slot * from,
                                std::vector<Slot *> & visited,
                                std::vector<Slot *> & final_path)
{
  if (!current || !current->_path)
    return false;

  // visited.push_back(current);
  visited.push_back(from);

  if (current->_path->isStart())
  {
    final_path.push_back(current);
    return true;
  }

  if (isConnectedABC(from, current, current->_T))
    if (std::find(visited.begin(), visited.end(), current->_T) == visited.end() &&
        isConnectedToStartThrough(current->_T, current, visited, final_path))
    {
      final_path.push_back(current);
      return true;
    }

  if (isConnectedABC(from, current, current->_R))
    if (std::find(visited.begin(), visited.end(), current->_R) == visited.end() &&
        isConnectedToStartThrough(current->_R, current, visited, final_path))
    {
      final_path.push_back(current);
      return true;
    }

  if (isConnectedABC(from, current, current->_B))
    if (std::find(visited.begin(), visited.end(), current->_B) == visited.end() &&
        isConnectedToStartThrough(current->_B, current, visited, final_path))
    {
      final_path.push_back(current);
      return true;
    }

  if (isConnectedABC(from, current, current->_L))
    if (std::find(visited.begin(), visited.end(), current->_L) == visited.end() &&
        isConnectedToStartThrough(current->_L, current, visited, final_path))
    {
      final_path.push_back(current);
      return true;
    }

  return false;
}

bool
Slot::isConnectedABC(Slot * A, Slot * B, Slot * C)
{
  if (!A || !B || !C || !A->_path || !B->_path || !C->_path)
    return false;

  if (B->T() == A)
  {
    if (B->R() == C)
    {
      if (B->_path->connectivity().TR() && B->_path->T() && B->_path->R() && A->_path->B() &&
          C->_path->L())
        return true;
    }
    if (B->B() == C)
    {
      if (B->_path->connectivity().TB() && B->_path->T() && B->_path->B() && A->_path->B() &&
          C->_path->T())
        return true;
    }
    if (B->L() == C)
    {
      if (B->_path->connectivity().TL() && B->_path->T() && B->_path->L() && A->_path->B() &&
          C->_path->R())
        return true;
    }
  }

  if (B->R() == A)
  {
    if (B->B() == C)
    {
      if (B->_path->connectivity().RB() && B->_path->R() && B->_path->B() && A->_path->L() &&
          C->_path->T())
        return true;
    }
    if (B->L() == C)
    {
      if (B->_path->connectivity().RL() && B->_path->R() && B->_path->L() && A->_path->L() &&
          C->_path->R())
        return true;
    }
    if (B->T() == C)
    {
      if (B->_path->connectivity().RT() && B->_path->R() && B->_path->T() && A->_path->L() &&
          C->_path->B())
        return true;
    }
  }

  if (B->B() == A)
  {
    if (B->L() == C)
    {
      if (B->_path->connectivity().BL() && B->_path->B() && B->_path->L() && A->_path->T() &&
          C->_path->R())
        return true;
    }
    if (B->T() == C)
    {
      if (B->_path->connectivity().BT() && B->_path->B() && B->_path->T() && A->_path->T() &&
          C->_path->B())
        return true;
    }
    if (B->R() == C)
    {
      if (B->_path->connectivity().BR() && B->_path->B() && B->_path->R() && A->_path->T() &&
          C->_path->L())
        return true;
    }
  }

  if (B->L() == A)
  {
    if (B->T() == C)
    {
      if (B->_path->connectivity().LT() && B->_path->L() && B->_path->T() && A->_path->R() &&
          C->_path->B())
        return true;
    }
    if (B->R() == C)
    {
      if (B->_path->connectivity().LR() && B->_path->L() && B->_path->R() && A->_path->R() &&
          C->_path->L())
        return true;
    }
    if (B->B() == C)
    {
      if (B->_path->connectivity().LB() && B->_path->L() && B->_path->B() && A->_path->R() &&
          C->_path->T())
        return true;
    }
  }

  return false;
}
