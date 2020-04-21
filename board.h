#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include "square.h"
#include "state.h"
#include "info.h"

class TextDisplay;
template <typename InfoType, typename StateType> class Observer;
class InvalidMove{};

class Board {
  TextDisplay *td = nullptr; // The text display.
  Observer<Info, State> *ob = nullptr; //graphics display pointer
  int size = 8;
  string lastMove;
  bool hasBlackKingMoved;
  bool hasWhiteKingMoved;
  bool hasWhiteRookAMoved;
  bool hasWhiteRookHMoved;
  bool hasBlackRookAMoved;
  bool hasBlackRookHMoved;
  vector<string> whiteCheckLocations; //stores the locations of white pieces that are checking the black king
  vector<string> blackCheckLocations; //stores the locations of black pieces that are checking the white king
 public:
   std::vector<std::vector<Square>> theBoard;  // The actual grid.
   vector<string> kingLocations; /*stores locations of kings for a variety of reasons
   one is that there can be only one king on the board so storing the location
   of current kings for set up purposes is useful
   we can also more easily check if a king is in checkmate
   index [0] has the location of the white king and index [1]*/
  ~Board();
  vector<string> validMoves(Square &s) const;
  bool isPinned(Square &s);
  bool isChecked(Colour c);
  void isAttacked();
  void setObserver(Observer<Info, State> *ob);
  bool isStalemate(Colour c) const;
  Colour isCheckmate(Colour c) const; // is there checkmate? and returns who won if so
  void init(); // Sets up an n x n grid.  Clears old grid, if necessary.
  void setPiece(int r, int c, Colour colour, Piece piece);  // Plays piece at row r, col c.

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

char convert(int i);

int convertBackwards(char i);

#endif
