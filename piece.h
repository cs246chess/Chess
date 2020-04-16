#ifndef PIECE_H
#define PIECE_H

class Piece {
  int row;
  int col;
  char color;

  virtual bool validMove(int col, int row) = 0;
  virtual void move(int col, int row) = 0;
  virtual int getRow() = 0;
  virtual int getCol() = 0;
  virtual char getColor() = 0;
};
#endif
