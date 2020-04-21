#include <iostream>
#include <string>
#include <vector>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay() {
  for (int i = 0; i < 8; i++) {
    theDisplay[i].resize(8);
  }
  for (int c = 0; c < 8; c++) {
    for (int r = 0; r < 8; r++) {
      if (c % 2 == 0 && r % 2 == 0) {
        theDisplay[c][r].emplace_back(' ');
      } else if (c % 2 == 0 &&  r % 2 != 0) {
        theDisplay[c][r].emplace_back('_');
      } else if (c % 2 != 0 &&  r % 2 == 0) {
        theDisplay[c][r].emplace_back('_');
      } else {
        theDisplay[c][r].emplace_back(' ');
      }
    }
  }
};

void TextDisplay::notify(Subject<Info, State> &whoFrom) {
  int row = whoFrom.getInfo().row;
  int col = whoFrom.getInfo().col;
  int colour = whoFrom.getInfo().colour;
  Piece piece = whoFrom.getInfo().piece;
  if (colour = Colour::Black) {
    if (piece == Piece::Pawn) {
      theDisplay[row][col] = "p";
    }
    if (piece == Piece::Rook) {
      theDisplay[row][col] = "r";
    }
    if (piece == Piece::King) {
      theDisplay[row][col] = "k";
    }
    if (piece == Piece::Bishop) {
      theDisplay[row][col] = "b";
    }
    if (piece == Piece::Knight) {
      theDisplay[row][col] = "k";
    }
    if (piece == Piece::Queen) {
      theDisplay[row][col] = "q";
    }
  } else if (colour = Colour::White) {
    if (piece == Piece::Pawn) {
      theDisplay[row][col] = "P";
    }
    if (piece == Piece::Rook) {
      theDisplay[row][col] = "R";
    }
    if (piece == Piece::King) {
      theDisplay[row][col] = "K";
    }
    if (piece == Piece::Bishop) {
      theDisplay[row][col] = "B";
    }
    if (piece == Piece::Knight) {
      theDisplay[row][col] = "K";
    }
    if (piece == Piece::Queen) {
      theDisplay[row][col] = "Q";
    }
  } else {
    if (row % 2 == 0 && col % 2 == 0) {
      theDisplay[row][col] = ' ';
    } else if (row % 2 == 0 &&  col % 2 != 0) {
      theDisplay[row][col] = '_';
    } else if (row % 2 != 0 &&  col % 2 == 0) {
      theDisplay[row][col] = '_';
    } else {
      theDisplay[row][col] = ' ';
    }
  }
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 8; i++) {
    out << 8 - i;
    for (int j = 0; j < 8; j++) {
      out << td[i][j];
    }
    out << endl;
  }
  out << endl;
  out << "  " << "abcdefgh" << endl;
  return out;
}
