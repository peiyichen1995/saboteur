#include "Board.h"
#include <iostream>

int
main()
{
  // Board
  Board B(5, 9);

  // connectivity
  Connectivity conn1(false, true, false, false, false, false);
  Connectivity conn2(true, true, false, true, false, false);
  Connectivity conn3(true, true, true, true, true, true);
  Connectivity conn4(false, false, false, true, false, false);
  Connectivity conn5(false, false, false, false, false, true);
  Connectivity conn6(false, false, false, false, false, false);
  Connectivity conn7(true, false, true, false, true, false);
  Connectivity conn8(false, false, false, false, true, false);

  Path * C1P1 = new Path(conn1, true, false, true, false);
  Path * C2P1 = new Path(conn2, true, true, true, false);
  Path * C3P1 = new Path(conn3, true, true, true, true);
  Path * C4P1 = new Path(conn4, false, true, true, false);
  Path * C5P1 = new Path(conn5, false, false, true, true);
  Path * C6P1 = new Path(conn6, false, false, true, false);
  Path * C6P2 = new Path(conn6, true, false, true, true);
  Path * C6P3 = new Path(conn6, true, true, true, true);
  Path * C6P4 = new Path(conn6, false, true, true, false);
  Path * C6P5 = new Path(conn6, false, false, true, true);
  Path * C6P6 = new Path(conn6, false, false, false, true);
  Path * C7P1 = new Path(conn7, true, true, false, true);
  Path * C8P1 = new Path(conn8, false, true, false, true);
  Path * C6P7 = new Path(conn6, true, false, true, false);
  Path * C6P8 = new Path(conn6, false, true, false, true);

  B.placePathInSlot(C1P1, 0, 0);
  B.placePathInSlot(C2P1, 0, 1);
  B.placePathInSlot(C3P1, 0, 2);
  B.placePathInSlot(C4P1, 0, 3);
  B.placePathInSlot(C5P1, 0, 4);
  B.placePathInSlot(C6P1, 1, 0);
  B.placePathInSlot(C6P2, 1, 1);
  B.placePathInSlot(C6P3, 1, 2);
  B.placePathInSlot(C6P4, 1, 3);
  B.placePathInSlot(C6P5, 1, 4);
  B.placePathInSlot(C6P6, 2, 0);
  B.placePathInSlot(C7P1, 2, 1);
  B.placePathInSlot(C8P1, 2, 2);
  B.placePathInSlot(C6P7, 3, 0);
  B.placePathInSlot(C7P1, 3, 1);
  B.placePathInSlot(C6P8, 3, 2);

  B.print();
}
