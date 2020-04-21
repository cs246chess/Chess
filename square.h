
#ifndef SQUARE_H
#define SQUARE_H
#include "subject.h"
#include "observer.h"
#include "piece.h"

class Square : public Subject<Info, State>, public Observer<Info, State> {
  const int r, c;
  Piece p;
  Colour colour;
  bool isEmpty;
  Colour pieceColour; //colour of PIECE
  bool AttackedByWhite;
  bool AttackedByBlack;
  // Add other private members if necessary

 public:
  Square(int r, int c, Colour colour);

  void validMove(int row, int col);
  void setPiece(Piece p, char pc, Colour c);    // Place a piece of given colour here.
  void notify(Subject<Info, State> &whoFrom) override;// My neighbours will call this
  Info getInfo() const override;
};

class InvalidMove{

};
int abs(int x);
#endif
