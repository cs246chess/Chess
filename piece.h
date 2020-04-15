#ifndef PIECE_H
#define PIECE_H

//base class
class Piece {
  int row;
  int col;
  char color;

  virtual bool validMove(int col, int row) = 0;
  virtual void move(int col, int row) = 0;
  int getRow();
  int getCol();
  char getColor();
};

class Pawn : public piece {
  bool validMove(int col, int row) const override;
  void move(int col, int row) const override;
};

Class Queen: Public Piece {
    bool validMove(int row, int col) const override;
    void move(int row, int col) override;
};
#endif
