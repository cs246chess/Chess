#include "window.h"
#include "graphicsdisplay.h"
#include <iostream>
#include <string>

using namespace std;

GraphicsDisplay::GraphicsDisplay()  {
  for (int row = 0; row < 8; row++) {
    gd.drawBigString(50, 100, to_string(8 - row), 1);
    for (int col = 0; col < 8; col++) {
      if (row % 2 == 0 && col % 2 == 0) {
        gd.fillRectangle(50 * row, 200, 250, 250, Xwindow::Yellow);
      } else if (row % 2 == 0 &&  col % 2 != 0) {
        gd.fillRectangle(50 * row, 200, 250, 250, Xwindow::Green);
      } else if (row % 2 != 0 &&  col % 2 == 0) {
        gd.fillRectangle(50 * row, 200, 250, 250, Xwindow::Yellow);
      } else {
        gd.fillRectangle(50 * row, 200, 250, 250, Xwindow::Yellow);
      }
    }
  }
  for (char i = 'a'; i < 'h'; ++i) {
        gd.drawBigString(50, 100, to_string(i), 1);
    }
}



void GraphicsDisplay::notify(Subject<Info, State> &whoNotified) {
  int row = whoNotified.getInfo().row;
  int col = whoNotified.getInfo().col;
  Colour colour = whoNotified.getInfo().colour;
  Piece piece = whoNotified.getInfo().piece;
  if (colour == Colour::Black) {
    if (piece == Piece::Pawn) {
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::Black);
    }
    if (piece == Piece::Rook) {
      gd.fillCircle(50 * row, 50 * col, 50,  Xwindow::Black);
      gd.fillRectangle(50 * row, 50 * col, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::Black);
    }
    if (piece == Piece::King) {
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillRectangle(50 * row, 50 * col, 10, 20, Xwindow::Black);
    }
    if (piece == Piece::Bishop) {
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::Black);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 10, Xwindow::Black);
    }
    if (piece == Piece::Knight) {
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillArc(50 * row, 50 * col, 50, 50, 50, 60, Xwindow::Black);
    }
    if (piece == Piece::Queen) {
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::Black);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 10, Xwindow::Black);
      gd.fillArc(50 * row, 50 * col, 50, 50, 50, 60, Xwindow::Black);
    }
  } else if (colour == Colour::White) {
    if (piece == Piece::Pawn) {
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::White);
    }
    if (piece == Piece::Rook) {
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::White);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::White);
    }
    if (piece == Piece::King) {
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillRectangle(50 * row, 50 * col, 10, 20, Xwindow::White);
    }
    if (piece == Piece::Bishop) {
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::White);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 50, Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 10, Xwindow::White);
    }
    if (piece == Piece::Knight) {
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillArc(50 * row, 50 * col, 50, 50, 50, 60, Xwindow::White);
    }
    if (piece == Piece::Queen) {
      gd.fillCircle(50 * row, 50 * col, 50,  Xwindow::White);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 50,  Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 10,  Xwindow::White);
      gd.fillArc(50 * row, 50 * col, 50, 50, 50, 60, Xwindow::White);
    }
  } else {
    if (row % 2 == 0 && col % 2 == 0) {
      gd.fillRectangle(50 * row, 200, 250, 250, Xwindow::Yellow);
    } else if (row % 2 == 0 &&  col % 2 != 0) {
      gd.fillRectangle(50 * row, 200, 250, 250, Xwindow::Green);
    } else if (row % 2 != 0 &&  col % 2 == 0) {
      gd.fillRectangle(50 * row, 200, 250, 250, Xwindow::Green);
    } else {
      gd.fillRectangle(50 * row, 200, 250, 250, Xwindow::Yellow);
    }
  }
};


GraphicsDisplay::~GraphicsDisplay() {}
