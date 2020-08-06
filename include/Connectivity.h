#pragma once

class Connectivity
{
public:
  // constructor
  Connectivity(bool TR, bool TB, bool TL, bool RB, bool RL, bool BL)
    : _TR(TR), _TB(TB), _TL(TL), _RB(RB), _RL(RL), _BL(BL)
  {
  }

  int cardinality() { return (int)_TR + (int)_TB + (int)_TL + (int)_RB + (int)_RL + (int)_BL; }

  // return connectivity between two directions
  bool TR() { return _TR; }
  bool TB() { return _TB; }
  bool TL() { return _TL; }
  bool RB() { return _RB; }
  bool RL() { return _RL; }
  bool BL() { return _BL; }

  bool RT() { return _TR; }
  bool BT() { return _TB; }
  bool LT() { return _TL; }
  bool BR() { return _RB; }
  bool LR() { return _RL; }
  bool LB() { return _BL; }

protected:
private:
  bool _TR;
  bool _TB;
  bool _TL;
  bool _RB;
  bool _RL;
  bool _BL;
};
