#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include "square.h"
#include "state.h"
#include "info.h"
#include "textdisplay.h"
using namespace std;

class TextDisplay;
template <typename InfoType, typename StateType> class Observer;
class InvalidMove{};

class Board {
  TextDisplay *td = nullptr; // The text display.
  //GraphicsDisplay *gd = nullptr; //graphics display pointer
  int size = 8;
  vector<string> whiteCheckLocations; //stores the locations of white pieces that are checking the black king
  vector<string> blackCheckLocations; //stores the locations of black pieces that are checking the white king
 public:
   string lastMove;
   std::vector<std::vector<Square>> theBoard;  // The actual grid.
   vector<string> kingLocations[2]; /*stores locations of kings for a variety of reasons
   one is that there can be only one king on the board so storing the location
   of current kings for set up purposes is useful
   we can also more easily check if a king is in checkmate
   index [0] has the location of the white king and index [1]*/
   //booleans to help with castling.
   bool hasBlackKingMoved;
   bool hasWhiteKingMoved;
   bool hasWhiteRookAMoved;
   bool hasWhiteRookHMoved;
   bool hasBlackRookAMoved;
   bool hasBlackRookHMoved;
  ~Board();
  vector<string> validMoves(Square s); //returns a vector containing all valid squares the passed piece can move to
  bool isPinned(Square s); //returns true if a piece on a given square is pinned against its king and false if it is not
  bool isChecked(Colour c); //returns true if the given colour king is in check
  void isAttacked();//goes over the board and checks to see if squares are attacked by white/black
  bool isStalemate(Colour c);//checks if a given colour player has any valid moves to make
  Colour isCheckmate(Colour c); //checks if the given colour's king is in checkmate, and
  //returns the colour of the player who won if they are in checkmate.
  void init(); // Sets up an n x n grid.  Clears old grid, if necessary.
  void setPiece(int r, int c, Colour colour, Piece piece);  // Plays piece at row r, col c.

  friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

char convert(int i);

int convertBackwards(char i);

#endif
