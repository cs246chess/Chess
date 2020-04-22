
#ifndef SQUARE_H
#define SQUARE_H
#include "subject.h"
#include "observer.h"
#include "info.h"
#include <iostream>

class Square : public Subject<Info, State>, public Observer<Info, State> {

  public:
  int r, c;
  Piece piece = Piece::Empty;
  Colour colour;
  Colour pieceColour; //colour of PIECE
  bool AttackedByWhite;
  bool AttackedByBlack;
  Square();
  Square(int r, int c, Colour colour);
  bool getAttacked(Colour c);
  bool validMove(int row, int col);
  void setPiece(Piece p, Colour c);    // Place a piece of given colour here.
  void notify(Subject<Info, State> &whoFrom) override;// My neighbours will call this
  Info getInfo() const override;
  friend std::ostream &operator<<(std::ostream &out, const Square &sq);
};
int abso(int x);
#endif
