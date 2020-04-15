#ifndef PIECE_H
#define PIECE_H

class Piece {
  int row;
  int col;
  char color;

  virtual bool valid_move(int, int) = 0;
  virtual void move(int, int) = 0;
  virtual int getRow() = 0;
  virtual int getCol() = 0;
};
#endif
