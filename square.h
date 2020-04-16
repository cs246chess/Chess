#ifndef SQUARE_H
#define SQUARE_H
#include "subject.h"
#include "observer.h"
#include "piece.h"

class Square : public Subject<Info, State> , public Observer<Info, State> {
  const int r, c;
  char color;
  Piece p;
  bool isEmpty;
  // Add other private members if necessary

 public:
  Square(int r, int c, char color);

  void setPiece(Piece p);    // Place a piece of given colour here.
  void notify(Subject<Info, State>  &whoFrom) override;// My neighbours will call this
  Info getInfo() const override;
};
#endif
