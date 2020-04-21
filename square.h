
#ifndef SQUARE_H
#define SQUARE_H
#include "subject.h"
#include "observer.h"

class Square : public Subject<Info, State>, public Observer<Info, State> {

  public:
  const int r, c;
  Piece piece;
  Colour colour;
  bool isEmpty;
  Colour pieceColour; //colour of PIECE
  bool AttackedByWhite;
  bool AttackedByBlack;
  // Add other private members if necessary
  Square(int r, int c, Colour colour);
  void getAttacked(Colour c, bool t);
  void validMove(int row, int col);
  void setPiece(Piece p, Colour c);    // Place a piece of given colour here.
  void notify(Subject<Info, State> &whoFrom) override;// My neighbours will call this
  Info getInfo() const override;
};
int abs(int x);
#endif
