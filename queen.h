#ifndef QUEEN_H
#define QUEEN_H
#ifndef CELL_H
#define CELL_H
#include "piece.h"

Class Queen: Public Piece {
    bool validMove(int col, int row) const override;
    void move(int col, int row) override;
    int getCol() const override;
    int getRow() const override;
    char getColor() const override;
};
#endif
