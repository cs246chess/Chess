#include <iostream>
#include <string>
#include "window.h"

#include "graphicsdisplay.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay()  {
  for (int row = 0; row < 8; i++) {
    gd.drawBigString(50, 100, to_string(8 - c), 1);
    for (int col = 0; col < 8; i++) {
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
  int color = whoNotified.getInfo().color;
  Piece piece = whoNotified.getInfo().piece;
  if (color = Color::Black) {
    if (piece == "Pawn") {
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::Black);
    }
    if (piece == "Rook") {
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::Black);
    }
    if (piece == "King") {
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillRectangle(50 * row, 50 * col, 10, 20, Xwindow::Black);
    }
    if (piece == "Bishop") {
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 10, 20, Xwindow::Black);
    }
    if (piece == "Knight") {
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillArc(50 * row, 50 * col, 50, 50, Xwindow::Black);
    }
    if (piece == "Queen") {
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::Black);
      gd.fillCircle(50 * row, 50 * col, 10, 20, Xwindow::Black);
      gd.fillArc(50 * row, 50 * col, 50, 50, Xwindow::Black);
    }
  } else (color = Color::White) {
    if (piece == "Pawn") {
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::White);
    }
    if (piece == "Rook") {
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::White);
    }
    if (piece == "King") {
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillRectangle(50 * row, 50 * col, 10, 20, Xwindow::White);
    }
    if (piece == "Bishop") {
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 10, 20, Xwindow::White);
    }
    if (piece == "Knight") {
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillArc(50 * row, 50 * col, 50, 50, Xwindow::White);
    }
    if (piece == "Queen") {
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillRectangle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 50, 50, Xwindow::White);
      gd.fillCircle(50 * row, 50 * col, 10, 20, Xwindow::White);
      gd.fillArc(50 * row, 50 * col, 50, 50, Xwindow::White);
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
