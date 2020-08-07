#include "Path.h"

Path::Path(Connectivity conn, bool T, bool R, bool B, bool L)
  : Card(), _conn(conn), _T(T), _R(R), _B(B), _L(L)
{
  draw();
}

void
Path::draw()
{
  _pixels = pixelType0();

  if (_T)
  {
    _pixels[0][2] = "\033[38;5;236m███\033[0m";
    _pixels[1][2] = "\033[38;5;236m███\033[0m";
  }
  if (_R)
  {
    _pixels[2][3] = "\033[38;5;236m█████\033[0m";
    _pixels[2][4] = "\033[38;5;236m█\033[0m";
  }
  if (_B)
  {
    _pixels[3][2] = "\033[38;5;236m███\033[0m";
    _pixels[4][2] = "\033[38;5;236m███\033[0m";
  }
  if (_L)
  {
    _pixels[2][0] = "\033[38;5;236m█\033[0m";
    _pixels[2][1] = "\033[38;5;236m█████\033[0m";
  }

  if (_conn.cardinality() == 0)
  {
  }
  else if (_conn.cardinality() == 1 || _conn.cardinality() == 3 || _conn.cardinality() == 6)
    _pixels[2][2] = "\033[38;5;236m███\033[0m";
  else
    std::cerr << "unsupported cardinality = " << _conn.cardinality() << std::endl;
}

void
Path::rotate()
{
  // rotate T, R, B, L
  bool tempT = _T;
  bool tempR = _R;
  bool tempB = _B;
  bool tempL = _L;

  _T = tempB;
  _B = tempT;
  _R = tempL;
  _L = tempR;

  _conn.rotate();

  draw();
}
