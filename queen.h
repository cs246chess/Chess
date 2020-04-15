#ifndef QUEEN_H
#define QUEEN_H
#ifndef CELL_H
#define CELL_H
#include "piece.h"

Class Queen: Public Piece {
    virtual bool validMove(int col, int row) const override;
    virtual void move(int col, int row) override;
    virtual int getCol() const override;
    virtual int getRow() const override;
    virtual char getColour() const override;
};
#endif
