#ifndef SQUARE_H
#define SQUARE_H
#include "subject.h"
#include "observer.h"
#include "piece.h"

<<<<<<< HEAD
class Square : public Subject, public Observer {
=======
class Square : public Subject<Info, State> , public Observer<Info, State> {
>>>>>>> 62e2f92478e18ed7f600573b3a103942ec07f367
  const int r, c;
  char color;
  Piece p;
  bool isEmpty;
  // Add other private members if necessary

 public:
  Square(int r, int c, char color);

  void setPiece(Piece p);    // Place a piece of given colour here.
<<<<<<< HEAD
  void notify(Subject< &whoFrom) override;// My neighbours will call this
=======
  void notify(Subject<Info, State>  &whoFrom) override;// My neighbours will call this
>>>>>>> 62e2f92478e18ed7f600573b3a103942ec07f367
  Info getInfo() const override;
};
#endif
