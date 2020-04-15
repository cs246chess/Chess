#ifndef PAWN_H
#define PAWN_H

class piece;

class Pawn : public piece {
  bool validMove(int col, int row) const override;
  void move(int col, int row) const override;
  int getCol() const override;
  int getRow() const override;
  char getColor() const override;
};
