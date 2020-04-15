#ifndef PAWN_H
#define PAWN_H

class piece;

class Pawn : public piece {
  bool validMove(int col, int row);
  void move(int col, int row);
}
