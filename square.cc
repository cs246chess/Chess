#include "square.h"
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::string;

int abs(int x) {
  if (x < 0) {
    return x * -1;
  }
  return x;
}

Square(int r, int c, Colour colour) {

}

void Square::Square::setPiece(Piece p, Colour colour, Colour c) {    // Place a piece of given colour here.
this->p = p;
  this->pColour = c;
}
void Square::Square::validMove(int row, int col){
  if (this->p == Piece::Pawn) { //Pawn moves
    if (this->pColour == Colour::Black) {
      if (this->r - row != 1 || this->r - row != 2) {
        return false;
      } else if (this->r - row == 2) {
        if (this->r != 7) {
          return false;
        } else if (this->c - col != 0) {
          return false;
        }
      } else if (this->r - row == 1) {
        if (abs(this->c - col) > 1) {
          return false;
        }
      }
    } else if if (this->pColour == Colour::white) {
      if (row - this->r != 1 || row - this->r != 2) {
        return false;
      } else if (row - this->r == 2) {
        if (this->r != 2) {
          return false;
        } else if (this->c - col != 0) {
          return false;
        }
      } else if (row - this->r == 1) {
        if (abs(this->c - col) > 1) {
          return false;
        }
      }
    }
  } else if (this->p == Piece::Bishop) { //Bishop moves
    if ((abs(this->r - row) != abs(this->c - col)) || this->r - row == 0 || this->c - col == 0) {
      return false;
    }
  } else if (this->p == Piece::Rook) { //Rook Moves
    if ((this->r - row != 0) && (this->c - col != 0)) {
      return false;
    } else if ((this->r - row == 0) && (this->c - col == 0)) {
      return false;
    }
  } else if (this->p == Piece::Queen) { //Queen moves
    if ((abs(this->r - row) != abs(this->c - col)) && (this->r - row != 0) && (this->c - col != 0)) {
      return false;
    } else if ((this->r - row == 0) && (this->c - col == 0)) {
      return false;
    }
  } else if (this->p == Piece::Knight) {
    if ((abs(this->r - row) == 2) && (abs(this->c - col == 1))) {
      return true;
    } else if ((abs(this->r - row) == 1) && (abs(this->c - col) == 2)) {
      return true;
    } else {
      return false;
    }
  } else if (this->p == Piece::King) {
    if ((abs(this->r - row) > 1) && (abs(this->c - col) > 1)) {
      return false;
    } else if ((this->r - row == 0) && (this->c - col == 0)) {
      return false;
    }
  }
  return true;
}

void Square::notify(Subject<Info, State> &whoFrom) {// My neighbours will call this
  
}


Info getInfo() const {
  return Info{r, c, colour, p};
}
