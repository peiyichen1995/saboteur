#include "Connectivity.h"

void
Connectivity::rotate()
{
  bool tempTR = _TR;
  bool tempTL = _TL;
  bool tempRB = _RB;
  bool tempBL = _BL;

  _TR = tempBL;
  _TL = tempRB;
  _RB = tempTL;
  _BL = tempTR;
}
