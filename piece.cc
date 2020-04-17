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
      }
      //2 square jump from starting position
      else if ((this->row == 7) && (row == 5)) {
        return true;
      } else {
        return false;
      }
    }
    //white pawn
    else if (this->color == 'w') {
      if (row - this->row == 1) {
        return true;
      }
      //2 square jump from starting position
      else if ((this->row == 2) && (row == 4)) {
        return true;
      } else {
        return false;
      }
    }
  }
  //capture
  else if ((this->col - col == 1) || (this->col - col == -1)) {
    //black pawn
    if (this->color == 'b') {
      if ((this->row) - row == 1) {
        return true;
      } else {
        return false;
      }
    }
    //white pawn
    else if (this->color == 'w') {
      if (row - this->row == 1) {
        return true;
      } else {
        return false;
      }
    }
  }
}

bool Bishop::validMove(int col, int row) {
  //moving in a up rightwards direction or a down leftwards direction
  if (((this->col - col) == (this->row - row)) && (this->col != 0)) {
    return true;
  }
//moving in a up leftwards direction or a down rightwards direction
  else if ((this->col - col) == -1 * (this->row - row)) {
    return true;
  } else {
    return false;
  }
}

bool Rook::validMove(int col, int row) {
  //staying on a column
  if ((this->col == col) && (this->row != row)) {
    return true;
  }
  //staying on a rank
  else if ((this->row == row) && (this->col != col)) {
    return true;
  } else {
    return false;
  }
}

bool Queen::validMove(int col, int row) {
  //moving like a rook
  if ((this->col == col) && (this->row != row)) {
    return true;
  } else if ((this->row == row) && (this->col != col)) {
    return true;
  }
  //moving like a bishop
  else if (((this->col - col) == (this->row - row)) && (this->col != 0)) {
    return true;
  } else if ((this->col - col) == -1 * (this->row - row)) {
    return true;
  } else {
    return false;
  }
}

bool Knight::validMove(int col, int row) {
  // moving upwards by two spaces
  if ((col - this->col) == 2) {
    //moving left
    if (this->row - row == 1) {
      return true;
    }
    //moving right
    else if (row - this->row == 1) {
      return true;
    }
  }
  //moving down
  else if ((this->col - col) == 2) {
    //moving left
    if (this->row - row == 1) {
      return true;
    }
    //moving right
    else if (row - this->row == 1) {
      return true;
    }
  }
  //moving left
  else if ((this->row - row) == 2) {
    //moving down
    if (this->col - col == 1) {
      return true;
    }
    //moving up
    else if (col - this->col == 1) {
      return true;
    }
  }
  //moving right
  else if ((row - this->row) == 2) {
    //moving down
    if (this->col - col == 1) {
      return true;
    }
    //moving up
    else if (col - this->col == 1) {
      return true;
    }
  }
}
