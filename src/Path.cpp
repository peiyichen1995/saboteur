#include "Path.h"

Path::Path(Connectivity conn, bool T, bool R, bool B, bool L)
  : _conn(conn), _T(T), _R(R), _B(B), _L(L), _pixels(pixelType0())
{
  if (T)
    _pixels[1][2] = "\033[1;31m ║ \033[0m";
  if (R)
    _pixels[2][3] = "\033[1;31m══\033[0m";
  if (B)
    _pixels[3][2] = "\033[1;31m ║ \033[0m";
  if (L)
    _pixels[2][1] = "\033[1;31m══\033[0m";

  if (_conn.cardinality() == 0)
  {
  }
  else if (_conn.cardinality() == 1)
  {
    if (_conn.TR())
      _pixels[2][2] = "\033[1;31m ╚═\033[0m";
    if (_conn.TB())
      _pixels[2][2] = "\033[1;31m ║ \033[0m";
    if (_conn.TL())
      _pixels[2][2] = "\033[1;31m═╝ \033[0m";
    if (_conn.RB())
      _pixels[2][2] = "\033[1;31m ╔═\033[0m";
    if (_conn.RL())
      _pixels[2][2] = "\033[1;31m═══\033[0m";
    if (_conn.BL())
      _pixels[2][2] = "\033[1;31m═╗ \033[0m";
  }
  else if (_conn.cardinality() == 3)
  {
    if (_conn.TL() && _conn.BL())
      _pixels[2][2] = "\033[1;31m═╣ \033[0m";
    if (_conn.TR() && _conn.BR())
      _pixels[2][2] = "\033[1;31m ╠═\033[0m";
    if (_conn.TL() && _conn.TR())
      _pixels[2][2] = "\033[1;31m═╩═\033[0m";
    if (_conn.BL() && _conn.BR())
      _pixels[2][2] = "\033[1;31m═╦═\033[0m";
  }
  else if (_conn.cardinality() == 6)
    _pixels[2][2] = "\033[1;31m═╬═\033[0m";
  else
    std::cerr << "unsupported cardinality = " << _conn.cardinality() << std::endl;
}

std::string
Path::operator()(int i, int j)
{
  return _pixels[i][j];
}
