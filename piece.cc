#include "piece.h"
#include <string>

int Piece::getCol() {
  return this->col;
}

int Piece::getRow() {
  return this->row;
}

char Piece::getColor() {
  return this->color
}

bool Pawn::validMove(int col, int row) {
  //regular move
  if (col == this->col) {
    //black pawn
    if (this->color == 'b') {
      if ((this->row) - row == 1) {
        return true;
      } else if ((this->row == 7) && (row == 5)) {
        return true;
      } else {
        return false;
      }
    } else if (this->color == 'w') {
      if (row - this->row == 1) {
        return true;
      } else if ((this->row == 2) && (row == 4)) {
        return true;
      } else {
        return false;
      }
    }
  } else if ((this->col - col == 1) || (this->col - col == -1)) {
    if (this->color == 'b') {
      if ((this->row) - row == 1) {
        return true;
      } else {
        return false;
      }
    } else if (this->color == 'w') {
      if (row - this->row == 1) {
        return true;
      } else {
        return false;
      }
    }
  }
}

bool Bishop::validMove(int col, int row) {
  if ((this->col - col) == (this->row - row)) {
    return true;
  } else if ((this->col - col) == -1 * (this->row - row)) {
    return true;
  } else {
    return false;
  }
}
