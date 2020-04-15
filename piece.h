#ifndef PIECE_H
#define PIECE_H

//base class
Class Piece {
  int row;
  int col;
  char color;

  virtual bool validMove(int col, int row) = 0;
  int getRow();
  int getCol();
  char getColor();
};

Class Pawn : public piece {
  bool validMove(int col, int row) const override;
};

Class Queen : Public Piece {
  bool validMove(int row, int col) const override;
};

Class King : Public Piece {
  bool hasMoved = false;
  bool validMove(int row, int col) const override;
};

Class Rook : Public Piece {
  bool hasMoved = false;
  bool validMove(int row, int col) const override;
};

Class Knight : Public Piece {
  bool validMove(int row, int col) const override;
};

Class Pawn : Public Piece {
  bool validMove(int row, int col) const override;
};
#endif
