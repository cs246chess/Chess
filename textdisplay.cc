#include <iostream>
#include <string>
#include <vector>
#include "textdisplay.h"

TextDisplay::TextDisplay() {
  for (int i = 0; i < 8; i++) {
    theDisplay[i].resize(8);
  }
  for (int c = 0; c < 8; r++) {
    for (int r = 0; r < 8; c++) {
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

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
  int row = whoNotified.getInfo().row;
  int col = whoNotified.getInfo().col;
  int color = whoNotified.getInfo().color;
  Piece piece = whoNotified.getInfo().piece;
  if (color = Color::Black) {
    if (piece == "Pawn") {
      theDisplay[row][col] = "p";
    }
    if (piece == "Rook") {
      theDisplay[row][col] = "r";
    }
    if (piece == "King") {
      theDisplay[row][col] = "k";
    }
    if (piece == "Bishop") {
      theDisplay[row][col] = "b";
    }
    if (piece == "Knight") {
      theDisplay[row][col] = "k";
    }
    if (piece == "Queen") {
      theDisplay[row][col] = "q";
    }
  } else (color = Color::White) {
    if (piece == "Pawn") {
      theDisplay[row][col] = "P";
    }
    if (piece == "Rook") {
      theDisplay[row][col] = "R";
    }
    if (piece == "King") {
      theDisplay[row][col] = "K";
    }
    if (piece == "Bishop") {
      theDisplay[row][col] = "B";
    }
    if (piece == "Knight") {
      theDisplay[row][col] = "K";
    }
    if (piece == "Queen") {
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
}
