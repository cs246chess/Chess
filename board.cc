#include "board.h"

void Board::init() {
  theBoard.clear();
  for (int i = 0; i < 8; i++) {
    theBoard[i].resize(8);
  }
  for (int r = 0; r < 8; r++) {
    for (int c = 0; c < 8; c++) {
      theBoard[r][c].r = r + 1;
      theBoard[r][c].c = c + 1;
      theBoard[r][c].isEmpty = true;
      theBoard[r][c].piece = Piece::Empty;
      theBoard[r][c].pieceColour = Color::NoColour;
      if (c % 2 == 0 && r % 2 == 0) {
        theBoard[c][r].colour = Color::White;
      } else if (c % 2 == 0 &&  r % 2 != 0) {
        theBoard[c][r].colour = Color::Black;
      } else if (c % 2 != 0 &&  r % 2 == 0) {
        theBoard[c][r].colour = Color::Black;
      } else {
        theBoard[c][r].colour = Color::White;
      }
    }
  }
  td = new Textdisplay();
}

void Board::setPiece(int r, int c, Colour colour, Piece piece) {
  theBoard[r-1][c-1].piece = piece;
  theBoard[r-1][c-1].pieceColour = colour;
  State newS;
  newS.type = StateType::MovedPiece;
  newS.pieceColour = s.pieceColour;
  newS.piece = s.piece;
  theBoard[r-1][c-1].setState(newS);
  theBoard[r-1][c-1].notifyObservers();
  td->notify(theBoard[r-1][c-1]);
}

void Board::setObserver(Observer<Info, State> *ob) {
  this->ob = ob;
}

