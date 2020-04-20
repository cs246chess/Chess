#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <cstddef>
#include "square.h"
#include "state.h"
#include "info.h"

class TextDisplay;
template <typename InfoType, typename StateType> class Observer;
class InvalidMove{};

class Board {
  std::vector<std::vector<Square>> theBoard;  // The actual grid.
  TextDisplay *td = nullptr; // The text display.
  Observer<Info, State> *ob = nullptr; //graphics display pointer
  int size = 8;

 public:
  ~Board();

  void setObserver(Observer<Info, State> *ob);
  bool isStalemate() const;
  Colour isCheckmate() const; // is there checkmate? and returns who won if so
  void init(); // Sets up an n x n grid.  Clears old grid, if necessary.
  void setPiece(int r, int c, Colour colour, Piece piece);  // Plays piece at row r, col c.

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
