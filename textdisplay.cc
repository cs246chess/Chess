#include <iostream>
#include <string>
#include <vector>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay() {
  theDisplay.resize(8);
  for (int i = 0; i < 8; i++) {
    theDisplay[i].resize(8);
  }
  for (int c = 0; c < 8; c++) {
    for (int r = 0; r < 8; r++) {
      if (c % 2 == 0 && r % 2 == 0) {
        theDisplay[c][r] = ' ';
      } else if (c % 2 == 0 &&  r % 2 != 0) {
        theDisplay[c][r] = '_';
      } else if (c % 2 != 0 &&  r % 2 == 0) {
        theDisplay[c][r] = '_';
      } else {
        theDisplay[c][r] =' ';
      }
    }
  }
}

void TextDisplay::notify(Subject<Info, State> &whoFrom) {
  int row = whoFrom.getInfo().row;
  int col = whoFrom.getInfo().col;
  Colour colour = whoFrom.getInfo().colour;
  Piece piece = whoFrom.getInfo().piece;
  if (colour == Colour::Black) {
    if (piece == Piece::Pawn) {
      theDisplay[row-1][col-1] = 'p';
    }
    if (piece == Piece::Rook) {
      theDisplay[row-1][col-1] = 'r';
    }
    if (piece == Piece::King) {
      theDisplay[row-1][col-1] = 'k';
    }
    if (piece == Piece::Bishop) {
      theDisplay[row-1][col-1] = 'b';
    }
    if (piece == Piece::Knight) {
      theDisplay[row-1][col-1] = 'n';
    }
    if (piece == Piece::Queen) {
      theDisplay[row-1][col-1] = 'q';
    }
  } else if (colour == Colour::White) {
    if (piece == Piece::Pawn) {
      theDisplay[row-1][col-1] = 'P';
    }
    if (piece == Piece::Rook) {
      theDisplay[row-1][col-1] = 'R';
    }
    if (piece == Piece::King) {
      theDisplay[row-1][col-1] = 'K';
    }
    if (piece == Piece::Bishop) {
      theDisplay[row-1][col-1] = 'B';
    }
    if (piece == Piece::Knight) {
      theDisplay[row-1][col-1] = 'N';
    }
    if (piece == Piece::Queen) {
      theDisplay[row-1][col-1] = 'Q';
    }
  } else {
    if (row % 2 == 0 && col % 2 == 0) {
      theDisplay[row-1][col-1] = '_';
    } else if (row % 2 == 0 &&  col % 2 != 0) {
      theDisplay[row-1][col-1] = ' ';
    } else if (row % 2 != 0 &&  col % 2 == 0) {
      theDisplay[row-1][col-1] = ' ';
    } else {
      theDisplay[row-1][col-1] = '_';
    }
  }
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 8; i++) {
    out << 8 - i << " ";
    for (int j = 0; j < 8; j++) {
      out << td.theDisplay[i][j];
    }
    out << endl;
  }
  out << endl;
  out << "  " << "abcdefgh" << endl;
  return out;
}
