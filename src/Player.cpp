#include "Player.h"
#include "Slot.h"

void
Player::printHand()
{
  for (unsigned int h = 0; h < SLOT_PIXEL_HEIGHT; h++)
  {
    for (unsigned int j = 0; j < _hand.size(); j++)
    {
      for (unsigned int w = 0; w < SLOT_PIXEL_WIDTH; w++)
        std::cout << (*_hand[j])(h, w);
      std::cout << "   ";
    }
    std::cout << std::endl;
  }
}
