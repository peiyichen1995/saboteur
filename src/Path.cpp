#include "Path.h"

Path::Path(Connectivity conn, bool T, bool R, bool B, bool L)
  : Card(), _conn(conn), _T(T), _R(R), _B(B), _L(L)
{
  draw();
}

void
Path::draw(bool highlight)
{
  std::string colorPrepend = highlight ? "\033[38;5;10m" : "\033[38;5;236m";
  std::string colorAppend = "\033[0m";

  _pixels = pixelType0();

  if (_T)
  {
    _pixels[0][2] = colorPrepend + "███" + colorAppend;
    _pixels[1][2] = colorPrepend + "███" + colorAppend;
  }
  if (_R)
  {
    _pixels[2][3] = colorPrepend + "█████" + colorAppend;
    _pixels[2][4] = colorPrepend + "█" + colorAppend;
  }
  if (_B)
  {
    _pixels[3][2] = colorPrepend + "███" + colorAppend;
    _pixels[4][2] = colorPrepend + "███" + colorAppend;
  }
  if (_L)
  {
    _pixels[2][0] = colorPrepend + "█" + colorAppend;
    _pixels[2][1] = colorPrepend + "█████" + colorAppend;
  }

  if (_conn.cardinality() == 0)
  {
  }
  else if (_conn.cardinality() == 1 || _conn.cardinality() == 3 || _conn.cardinality() == 6)
    _pixels[2][2] = colorPrepend + "███" + colorAppend;
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
