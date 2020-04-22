#ifndef INFO_H
#define INFO_H
#include <cstddef>
#include "state.h"
 
struct Info {
  int col;
  int row;
  Colour colour;
  Piece piece;
  Colour pieceColour;
};

#endif
