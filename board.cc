#include "board.h"
using namespace std;

char convert(int i) {
  return ('a' + (i - 1));
}

int convertBackwards(char i){
  return ((i - 'a') + 1);
}

friend std::ostream &operator<<(std::ostream &out, const Board &b) {
  if (b.td != nullptr) {
    out << *b.td;
  }
  return out;
}

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
      theBoard[r][c].pieceColour = Colour::NoColour;
      if (c % 2 == 0 && r % 2 == 0) {
        theBoard[c][r].colour = Colour::White;
      } else if (c % 2 == 0 &&  r % 2 != 0) {
        theBoard[c][r].colour = Colour::Black;
      } else if (c % 2 != 0 &&  r % 2 == 0) {
        theBoard[c][r].colour = Colour::Black;
      } else {
        theBoard[c][r].colour = Colour::White;
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


bool Board::isStalemate(Colour c) const { //checks if the specified player is in stalemate
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (theBoard[i][j].pieceColour == c) {
        vector<string> moves = validMoves(&theBoard[i][j]);
        if (moves.size() != 0) {
          return false;
        }
      }
    }
  }
  return true;
}

bool Board::isChecked(Colour c) { //checks if the specified player is in check
  if (c == Colour::White) {
    if (kingLocations[0].AttackedByBlack == true) {
      return true;
    }
  }
  else if (c == Colour::Black) {
    if (kingLocations[1].AttackedByWhite == true) {
      return true;
    }
  }
  return false;
}

bool Board::isAttacked() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      theBoard[i][j].AttackedByBlack = false;
      theBoard[i][j].AttackedByWhite = false;
    }
  }
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < sizel j++) {
      state newS;
      newS.type = StateType::MovedPiece;
      newS.pieceColour = s.pieceColour;
      newS.piece = s.piece;
      s.setState(newS);
      notifyObservers();
    }
  }
}

bool Board::isPinned(Square &s) {
  if (s.piece == Piece::King) {
    return false;
  }
  int PieceColour = 2;
  if (s.pieceColour == Colour::White) {
    PieceColour = 0;
  }
  else if (s.pieceColour == Colour::Black) {
    PieceColour = 1;
  }
  else if (s.pieceColour == Colour::NoColour) {
    return false;
  }
  if (s.r == kingLocations[PieceColour].r) { //if on equal row
    if (s.c > kingLocations[PieceColour].c) {
      for (int i = (kingLocations[PieceColour].c); i < s.c - 1; i++) {
        if (theBoard[s.r - 1][i].piece != Piece::Empty) {
          return false;
        }
      }
      for (int i = s.c; i <= 7; i++) {
        if ((theBoard[s.r - 1][i].piece == Piece::Queen) || (theBoard[s.r - 1][i].piece == Piece::Rook)) {
          if ((theBoard[s.r - 1][i].pieceColour != s.pieceColour)) {
            return true;
          }
          else {
            return false;
          }
        }
        else if (theBoard[s.r - 1][i].piece != Piece::Empty) {
          return false;
        }
      }
      return false;
    }
    if (s.c < kingLocations[PieceColour].c) {
      for (int i = s.c; i < (kingLocations[PieceColour].c) - 1; i++) {
        if (theBoard[s.r - 1][i].piece != Piece::Empty) {
          return false;
        }
      }
      for (int i = s.c - 2; i >= 0; i--) {
        if ((theBoard[s.r - 1][i].piece == Piece::Queen) || (theBoard[s.r - 1][i].piece == Piece::Rook)) {
          if ((theBoard[s.r - 1][i].pieceColour != s.pieceColour)) {
            return true;
          }
          else {
            return false;
          }
        }
        else if (theBoard[s.r - 1][i].piece != Piece::Empty) {
          return false;
        }
      }
      return false;
    }
  }
  if (s.c == kingLocations[PieceColour].c) { //if on equal column
    if (s.r > kingLocations[PieceColour].r) {
      for (int i = (kingLocations[PieceColour].r); i < s.r - 1; i++) {
        if (theBoard[i][s.c - 1].piece != Piece::Empty) {
          return false;
        }
      }
      for (int i = s.r; i <= 7; i++) {
        if ((theBoard[i][s.c - 1].piece == Piece::Queen) || (theBoard[i][s.c - 1].piece == Piece::Rook)) {
          if ((theBoard[i][s.c - 1].pieceColour != s.pieceColour)) {
            return true;
          }
          else {
            return false;
          }
        }
        else if (theBoard[i][s.c - 1].piece != Piece::Empty) {
          return false;
        }
      }
      return false;
    }
    if (s.r < kingLocations[PieceColour].r) {
      for (int i = s.r; i < (kingLocations[PieceColour].r) - 1; i++) {
        if (theBoard[i][s.c - 1].piece != Piece::Empty) {
          return false;
        }
      }
      for (int i = (s.r - 2); i >= 0; i--) {
        if ((theBoard[i][s.c - 1].piece == Piece::Queen) || (theBoard[i][s.c - 1].piece == Piece::Rook)) {
          if ((theBoard[i][s.c - 1].pieceColour != s.pieceColour)) {
            return true;
          }
          else {
            return false;
          }
        }
        else if (theBoard[s.r - 1][i].piece != Piece::Empty) {
          return false;
        }
      }
      return false;
    }
  }
  if (abs(s.r - kingLocations[PieceColour].r) == abs(s.c - kingLocations[PieceColour].c)) {
    int constSide = (s.r - kingLocations[PieceColour].r) / abs(s.r - kingLocations[PieceColour].r);
    int constUp = (s.c - kingLocations[PieceColour].c) / abs(s.c - kingLocations[PieceColour].c);
    int counter = s.c - 1 + constUp;
    for (int i = (s.r - 1 + constSide); i != (kingLocations[PieceColour].r - 1); i = i + constSide) {
      if (theBoard[i][counter].piece != Piece::Empty) {
        return false;
        counter += constUp;
      }
    }
    int reverseCounter = s.c - 1 + (constUp * -1);
    for (int i = (s.r - 1 + (constSide * - 1)); ((i >= 0) && (i <= 7)); i += (-1 * constSide)) {
      if ((theBoard[i][reverseCounter].piece == Piece::Bishop) || (theBoard[i][reverseCounter].piece == Piece::Queen)) {
        if (theBoard[i][reverseCounter].pieceColour != s.pieceColour) {
          return true;
        }
        else {
          return false;
        }
      }
      else if (theBoard[i][reverseCounter].piece != Piece::Empty) {
        return false;
      }
      reverseCounter += (-1 * constUp);
    }
    return false;
  }
  return false;
}

vector<string> Board::validMoves(Square &s) const {
  vector<string> moves;
  if (isPinned(s)) {
    return moves;
  }
  if (s.piece == Piece::Pawn) { //pawn legal moves
    if (s.pieceColour == Colour::Black) {
      if (s.c > 0) {
        if ((this->theBoard[s.r - 2][s.c - 1]).piece == Piece::Empty) {
          string s = " ";
          s[0] = convert(s.c);
          s = s + to_string(s.r - 1);
          moves.emplace_back(s);
          if (((this->theBoard[s.r - 3][s.c - 1]).piece == Piece::Empty) && (s.r == 7) {
            string s = " ";
            s[0] = convert(s.c);
            s = s + to_string(s.r - 2);
            moves.emplace_back(s);
          }
        }
      }
      if ((s.c - 2) >= 0) {
        if ((this->theBoard[s.r - 2][s.c - 2]).piece != Piece::Empty) {
          if (s.pieceColour != (this->theBoard[s.r - 2][s.c - 2]).pieceColour) {
            string s = " ";
            s[0] = convert((s.c - 1));
            s = s + to_string(s.r - 1);
            moves.emplace_back(s);
          }
        }
      }
      if (s.c <= 7) {
        if ((this->theBoard[s.r - 2][s.c]).piece != Piece::Empty) {
          if (s.pieceColour != (this->theBoard[s.r - 2][s.c]).pieceColour) {
            string s = " ";
            s[0] = convert(s.c + 1);
            s = s + to_string(s.r - 1);
            moves.emplace_back(s);
          }
        }
      }
      if (s.r == 4) {
        if ((convert(s.c + 1) == lastMove[2]) && (lastMove[2] == lastMove[0])) {
          if (theBoard[s.r - 1][convertBackwards(lastMove[4]) - 1]) {
            if (theBoard[s.r - 1][convertBackwards(lastMove[4]) - 1].pieceColour != s.pieceColour) {
              string s = " ";
              s[0] = convert(s.c + 1);
              s = s + to_string(s.r - 1);
              moves.emplace_back(s);
            }
          }
        }
        else if ((convert(s.c - 1) == lastMove[2]) && (lastMove[2] == lastMove[0])) {
          if (theBoard[s.r - 1][convertBackwards(lastMove[4])].piece == Piece::Pawn) {
            if (theBoard[s.r - 1][convertBackwards(lastMove[4])].pieceColour != s.pieceColour) {
              string s = " ";
              s[0] = convert(s.c - 1);
              s = s + to_string(s.r - 1);
              moves.emplace_back(s);
            }
          }
        }
      }
    }
    else if (s.pieceColour == Colour::White) {
      if ((this->theBoard[s.r][s.c - 1]).piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(s.c);
        s = s + to_string(s.r + 1);
        moves.emplace_back(s);
        if (((this->theBoard[s.r + 1][s.c - 1]).piece == Piece::Empty) && (s.r == 2) {
          string s = " ";
          s[0] = convert(s.c);
          s = s + to_string(s.r + 2);
          moves.emplace_back(s);
        }
      }
      if ((s.c - 2) >= 0) {
        if ((this->theBoard[s.r][s.c - 2]).piece != Piece::Empty) {
          if (s.pieceColour != (this->theBoard[s.r][s.c - 2]).pieceColour) {
            string s = " ";
            s[0] = convert(s.c - 1);
            s = s + to_string(s.r + 1);
            moves.emplace_back(s);
          }
        }
      }
      if (s.c <= 7) {
        if ((this->theBoard[s.r - 2][s.c]).piece != Piece::Empty) {
          if (s.pieceColour != (this->theBoard[s.r - 2][s.c]).pieceColour) {
            string s = " ";
            s[0] = convert(s.c + 1);
            s = s + to_string(s.r + 1);
            moves.emplace_back(s);
          }
        }
      }
      if (s.r == 5) {
        if ((convert(s.c + 1) == lastMove[2]) && (lastMove[2] == lastMove[0])) {
          if (theBoard[s.r - 1][convertBackwards(lastMove[4]) - 1]) {
            if (theBoard[s.r - 1][convertBackwards(lastMove[4])].pieceColour != s.pieceColour) {
              string s = " ";
              s[0] = convert(s.c + 1);
              s = s + to_string(s.r + 1);
              moves.emplace_back(s);
            }
          }
        }
        else if ((convert(s.c - 1) == lastMove[2]) && (lastMove[2] == lastMove[0])) {
          if (theBoard[s.r - 1][convertBackwards(lastMove[4])].piece == Piece::Pawn) {
            if (theBoard[s.r - 1][convertBackwards(lastMove[4])].pieceColour != s.pieceColour) {
              string s = " ";
              s[0] = convert(s.c - 1);
              s = s + to_string(s.r + 1);
              moves.emplace_back(s);
            }
          }
        }
      }
    }
  }
  else if (s.piece == Piece::Bishop) { //Bishop legal moves
    int row = s.r - 1;
    int col = s.c - 1;
    while ((row <= 7) && (col <= 7)) {
      row++;
      col++;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r - 1;
    col = s.c - 1;
    while ((row >= 0) && (col <= 7)) {
      row--;
      col++;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r - 1;
    col = s.c - 1;
    while ((row <= 7) && (col >= 0)) {
      row++;
      col--;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r - 1;
    col = s.c - 1;
    while ((row >= 0) && (col >= 0)) {
      row--;
      col--;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
  }
  else if (s.piece == Piece::Knight) { //Knight legal moves
    if (s.r <= 7) { //moving 1 upwards
      if (s.c <= 6) { //moving 2 rightwards
        if (theBoard[s.r][s.c + 1].piece == Piece::Empty) {
          string s = " ";
          s[0] = convert(s.c + 2);
          s = s + to_string(s.r + 1);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r][s.c + 1].pieceColour != s.pieceColour) {
          string s = " ";
          s[0] = convert(s.c + 2);
          s = s + to_string(s.r + 1);
          moves.emplace_back(s);
        }
      }
      if (s.c >= 3) { //moving 2 leftwards
        if (theBoard[s.r][s.c - 3].piece == Piece::Empty) {
          string s = " ";
          s[0] = convert(s.c - 2);
          s = s + to_string(s.r + 1);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r][s.c - 3].pieceColour != s.pieceColour) {
          string s = " ";
          s[0] = convert(s.c - 2);
          s = s + to_string(s.r + 1);
          moves.emplace_back(s);
        }
      }
    }
    if (s.r >= 2) { //moving 1 downwards
      if (s.c <= 6) { //moving 2 rightwards
        if (theBoard[s.r - 2][s.c + 1].piece == Piece::Empty) {
          string s = " ";
          s[0] = convert(s.c + 2);
          s = s + to_string(s.r - 1);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 2][s.c + 1].pieceColour != s.pieceColour) {
          string s = " ";
          s[0] = convert(s.c + 2);
          s = s + to_string(s.r - 1);
          moves.emplace_back(s);
        }
      }
      if (s.c >= 3) { //moving 2 leftwards
        if (theBoard[s.r - 2][s.c - 3].piece == Piece::Empty) {
          string s = " ";
          s[0] = convert(s.c - 2);
          s = s + to_string(s.r - 1);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 2][s.c - 3].pieceColour != s.pieceColour) {
          string s = " ";
          s[0] = convert(s.c - 2);
          s = s + to_string(s.r - 1);
          moves.emplace_back(s);
        }
      }
    }
    if (s.c <= 7) { //moving 1 rightwards
      if (s.r <= 6) { //moving 2 upwards
        if (theBoard[s.r + 1][s.c].piece == Piece::Empty) {
          string s = " ";
          s[0] = convert(s.c + 1);
          s = s + to_string(s.r + 2);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r + 1][s.c].pieceColour != s.pieceColour) {
          string s = " ";
          s[0] = convert(s.c + 1);
          s = s + to_string(s.r + 2);
          moves.emplace_back(s);
        }
      }
      if (s.r >= 3) { //moving 2 downwards
        if (theBoard[s.r - 3][s.c].piece == Piece::Empty) {
          string s = " ";
          s[0] = convert(s.c + 1);
          s = s + to_string(s.r - 2);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 3][s.c].pieceColour != s.pieceColour) {
          string s = " ";
          s[0] = convert(s.c + 1);
          s = s + to_string(s.r - 2);
          moves.emplace_back(s);
        }
      }
    }
    if (s.c >= 2) { //moving 1 leftwards
      if (s.r <= 6) { //moving 2 upwards
        if (theBoard[s.r + 1][s.c - 2].piece == Piece::Empty) {
          string s = " ";
          s[0] = convert(s.c - 1);
          s = s + to_string(s.r + 2);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r + 1][s.c - 2].pieceColour != s.pieceColour) {
          string s = " ";
          s[0] = convert(s.c - 1);
          s = s + to_string(s.r + 2);
          moves.emplace_back(s);
        }
      }
      if (s.r >= 3) { //moving 2 downwards
        if (theBoard[s.r - 3][s.c - 2].piece == Piece::Empty) {
          string s = " ";
          s[0] = convert(s.c - 1);
          s = s + to_string(s.r - 2);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 3][s.c - 2].pieceColour != s.pieceColour) {
          string s = " ";
          s[0] = convert(s.c - 1);
          s = s + to_string(s.r - 2);
          moves.emplace_back(s);
        }
      }
    }
  }
  else if (s.piece == Piece::King) { //King legal moves
    isAttacked();
    if (s.pieceColour == Colour::White) { //White King
      if (s.r <= 7) { //moving up with the king
        if ((theBoard[s.r][(s.c - 1)].piece == Piece::Empty) && (theBoard[s.r][(s.c - 1)].AttackedByBlack == false)) {
          string s = " ";
          s[0] = convert(s.c);
          s = s + to_string(s.r);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r][(s.c - 1)].pieceColour != s.pieceColour) {
          if (theBoard[s.r][(s.c - 1)].AttackedByBlack == false) {
            string s = " ";
            s[0] = convert(s.c);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
        }
        if (s.c <= 7) {
          if ((theBoard[s.r][(s.c)].piece == Piece::Empty) && (theBoard[s.r][(s.c)].AttackedByBlack == false)) {
            string s = " ";
            s[0] = convert(s.c + 1);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
          else if (theBoard[s.r][(s.c)].pieceColour != s.pieceColour) {
            if (theBoard[s.r][(s.c)].AttackedByBlack == false) {
              string s = " ";
              s[0] = convert(s.c + 1);
              s = s + to_string(s.r);
              moves.emplace_back(s);
            }
          }
        }
        if (s.c >= 2) {
          if ((theBoard[s.r][(s.c - 2)].piece == Piece::Empty) && (theBoard[s.r][(s.c - 2)].AttackedByBlack == false)) {
            string s = " ";
            s[0] = convert(s.c - 1);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
          else if (theBoard[s.r][(s.c - 2)].pieceColour != s.pieceColour) {
            if (theBoard[s.r][(s.c - 2)].AttackedByBlack == false) {
              string s = " ";
              s[0] = convert(s.c - 1);
              s = s + to_string(s.r);
              moves.emplace_back(s);
            }
          }
        }
      }
      if (s.r >= 2) { //moving down with the king
        if ((theBoard[s.r - 2][(s.c - 1)].piece == Piece::Empty) && (theBoard[s.r - 2][(s.c - 1)].AttackedByBlack == false)) {
          string s = " ";
          s[0] = convert(s.c);
          s = s + to_string(s.r - 1);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 2][(s.c - 1)].pieceColour != s.pieceColour) {
          if (theBoard[s.r - 2][(s.c - 1)].AttackedByBlack == false) {
            string s = " ";
            s[0] = convert(s.c);
            s = s + to_string(s.r - 1);
            moves.emplace_back(s);
          }
        }
        if (s.c <= 7) {
          if ((theBoard[s.r - 2][(s.c)].piece == Piece::Empty) && (theBoard[s.r - 2][(s.c)].AttackedByBlack == false)) {
            string s = " ";
            s[0] = convert(s.c + 1);
            s = s + to_string(s.r - 1);
            moves.emplace_back(s);
          }
          else if (theBoard[s.r - 2][(s.c)].pieceColour != s.pieceColour) {
            if (theBoard[s.r - 2][(s.c)].AttackedByBlack == false) {
              string s = " ";
              s[0] = convert(s.c + 1);
              s = s + to_string(s.r - 1);
              moves.emplace_back(s);
            }
          }
        }
        if (s.c >= 2) {
          if ((theBoard[s.r - 2][(s.c - 2)].piece == Piece::Empty) && (theBoard[s.r - 2][(s.c - 2)].AttackedByBlack == false)) {
            string s = " ";
            s[0] = convert(s.c - 1);
            s = s + to_string(s.r - 1);
            moves.emplace_back(s);
          }
          else if (theBoard[s.r - 2][(s.c - 2)].pieceColour != s.pieceColour) {
            if (theBoard[s.r - 2][(s.c - 2)].AttackedByBlack == false) {
              string s = " ";
              s[0] = convert(s.c - 1);
              s = s + to_string(s.r - 1);
              moves.emplace_back(s);
            }
          }
        }
      }
      if (s.c >= 2) { //moving left
        if ((theBoard[s.r - 1][(s.c - 2)].piece == Piece::Empty) && (theBoard[s.r - 1][(s.c - 2)].AttackedByBlack == false)) {
          string s = " ";
          s[0] = convert(s.c - 1);
          s = s + to_string(s.r);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 1][(s.c - 2)].pieceColour != s.pieceColour) {
          if (theBoard[s.r - 1][(s.c - 2)].AttackedByBlack == false) {
            string s = " ";
            s[0] = convert(s.c - 1);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
        }
      }
      if (s.c <= 7) { //moving right
        if ((theBoard[s.r - 1][(s.c)].piece == Piece::Empty) && (theBoard[s.r - 1][(s.c)].AttackedByBlack == false)) {
          string s = " ";
          s[0] = convert(s.c + 1);
          s = s + to_string(s.r);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 1][(s.c)].pieceColour != s.pieceColour) {
          if (theBoard[s.r - 1][(s.c)].AttackedByBlack == false) {
            string s = " ";
            s[0] = convert(s.c + 1);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
        }
      }
      //Castling
      if ((hasWhiteKingMoved == false) && (hasWhiteRookAMoved == false)) {
        if ((theBoard[0][2].AttackedByBlack == false) && (theBoard[0][3].AttackedByBlack == false) && (theBoard[0][4].AttackedByBlack == false)) {
          string s = " ";
          s[0] = convert(3);
          s = s + to_string(1);
          moves.emplace_back(s);
        }
      }
      if ((hasWhiteKingMoved == false) && (hasWhiteRookHMoved == false)) {
        if ((theBoard[0][6].AttackedByBlack == false) && (theBoard[0][5].AttackedByBlack == false)) {
          string s = " ";
          s[0] = convert(7);
          s = s + to_string(1);
          moves.emplace_back(s);
        }
      }
    }
    else if (s.pieceColour == Colour::Black) { //Black King
      if (s.r <= 7) { //moving up with the king
        if ((theBoard[s.r][(s.c - 1)].piece == Piece::Empty) && (theBoard[s.r][(s.c - 1)].AttackedByWhite == false)) {
          string s = " ";
          s[0] = convert(s.c);
          s = s + to_string(s.r);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r][(s.c - 1)].pieceColour != s.pieceColour) {
          if (theBoard[s.r][(s.c - 1)].AttackedByWhite == false) {
            string s = " ";
            s[0] = convert(s.c);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
        }
        if (s.c <= 7) {
          if ((theBoard[s.r][(s.c)].piece == Piece::Empty) && (theBoard[s.r][(s.c)].AttackedByWhite == false)) {
            string s = " ";
            s[0] = convert(s.c + 1);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
          else if (theBoard[s.r][(s.c)].pieceColour != s.pieceColour) {
            if (theBoard[s.r][(s.c)].AttackedByWhite == false) {
              string s = " ";
              s[0] = convert(s.c + 1);
              s = s + to_string(s.r);
              moves.emplace_back(s);
            }
          }
        }
        if (s.c >= 2) {
          if ((theBoard[s.r][(s.c - 2)].piece == Piece::Empty) && (theBoard[s.r][(s.c - 2)].AttackedByWhite == false)) {
            string s = " ";
            s[0] = convert(s.c - 1);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
          else if (theBoard[s.r][(s.c - 2)].pieceColour != s.pieceColour) {
            if (theBoard[s.r][(s.c - 2)].AttackedByWhite == false) {
              string s = " ";
              s[0] = convert(s.c - 1);
              s = s + to_string(s.r);
              moves.emplace_back(s);
            }
          }
        }
      }
      if (s.r >= 2) { //moving down with the king
        if ((theBoard[s.r - 2][(s.c - 1)].piece == Piece::Empty) && (theBoard[s.r - 2][(s.c - 1)].AttackedByWhite == false)) {
          string s = " ";
          s[0] = convert(s.c);
          s = s + to_string(s.r - 1);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 2][(s.c - 1)].pieceColour != s.pieceColour) {
          if (theBoard[s.r - 2][(s.c - 1)].AttackedByWhite == false) {
            string s = " ";
            s[0] = convert(s.c);
            s = s + to_string(s.r - 1);
            moves.emplace_back(s);
          }
        }
        if (s.c <= 7) {
          if ((theBoard[s.r - 2][(s.c)].piece == Piece::Empty) && (theBoard[s.r - 2][(s.c)].AttackedByWhite == false)) {
            string s = " ";
            s[0] = convert(s.c + 1);
            s = s + to_string(s.r - 1);
            moves.emplace_back(s);
          }
          else if (theBoard[s.r - 2][(s.c)].pieceColour != s.pieceColour) {
            if (theBoard[s.r - 2][(s.c)].AttackedByWhite == false) {
              string s = " ";
              s[0] = convert(s.c + 1);
              s = s + to_string(s.r - 1);
              moves.emplace_back(s);
            }
          }
        }
        if (s.c >= 2) {
          if ((theBoard[s.r - 2][(s.c - 2)].piece == Piece::Empty) && (theBoard[s.r - 2][(s.c - 2)].AttackedByWhite == false)) {
            string s = " ";
            s[0] = convert(s.c - 1);
            s = s + to_string(s.r - 1);
            moves.emplace_back(s);
          }
          else if (theBoard[s.r - 2][(s.c - 2)].pieceColour != s.pieceColour) {
            if (theBoard[s.r - 2][(s.c - 2)].AttackedByWhite == false) {
              string s = " ";
              s[0] = convert(s.c - 1);
              s = s + to_string(s.r - 1);
              moves.emplace_back(s);
            }
          }
        }
      }
      if (s.c >= 2) { //moving left
        if ((theBoard[s.r - 1][(s.c - 2)].piece == Piece::Empty) && (theBoard[s.r - 1][(s.c - 2)].AttackedByWhite == false)) {
          string s = " ";
          s[0] = convert(s.c - 1);
          s = s + to_string(s.r);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 1][(s.c - 2)].pieceColour != s.pieceColour) {
          if (theBoard[s.r - 1][(s.c - 2)].AttackedByWhite == false) {
            string s = " ";
            s[0] = convert(s.c - 1);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
        }
      }
      if (s.c <= 7) { //moving right
        if ((theBoard[s.r - 1][(s.c)].piece == Piece::Empty) && (theBoard[s.r - 1][(s.c)].AttackedByWhite == false)) {
          string s = " ";
          s[0] = convert(s.c + 1);
          s = s + to_string(s.r);
          moves.emplace_back(s);
        }
        else if (theBoard[s.r - 1][(s.c)].pieceColour != s.pieceColour) {
          if (theBoard[s.r - 1][(s.c)].AttackedByWhite == false) {
            string s = " ";
            s[0] = convert(s.c + 1);
            s = s + to_string(s.r);
            moves.emplace_back(s);
          }
        }
      }
      //Castling
      if ((hasBlackKingMoved == false) && (hasBlackRookAMoved == false)) {
        if ((theBoard[7][2].AttackedByWhite == false) && (theBoard[7][3].AttackedByWhite == false) && (theBoard[7][4].AttackedByBlack == false)) {
          string s = " ";
          s[0] = convert(3);
          s = s + to_string(1);
          moves.emplace_back(s);
        }
      }
      if ((hasBlackKingMoved == false) && (hasBlackRookHMoved == false)) {
        if ((theBoard[7][6].AttackedByWhite == false) && (theBoard[7][5].AttackedByWhite == false)) {
          string s = " ";
          s[0] = convert(7);
          s = s + to_string(1);
          moves.emplace_back(s);
        }
      }
    }
  }
  else if (s.piece == Piece::Queen) { //Queen legal moves
    //Moving like a Bishop
    int row = s.r - 1;
    int col = s.c - 1;
    while ((row <= 7) && (col <= 7)) {
      row++;
      col++;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r - 1;
    col = s.c - 1;
    while ((row >= 0) && (col <= 7)) {
      row--;
      col++;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r - 1;
    col = s.c - 1;
    while ((row <= 7) && (col >= 0)) {
      row++;
      col--;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r - 1;
    col = s.c - 1;
    while ((row >= 0) && (col >= 0)) {
      row--;
      col--;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    //Moving like a Rook
    row = s.r - 1;
    col = s.c - 1;
    while ((row <= 6)) {
      row++;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r;
    while ((row >= 1)) {
      row--;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r;
    while ((col <= 6)) {
      col++;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    col = s.c;
    while ((col >= 1)) {
      col--;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }

  }
  else if (s.piece == Piece::Rook) { //Rook legal moves
    int row = s.r - 1;
    int col = s.c - 1;
    while ((row <= 6)) {
      row++;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r;
    while ((row >= 1)) {
      row--;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    row = s.r;
    while ((col <= 6)) {
      col++;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
    col = s.c;
    while ((col >= 1)) {
      col--;
      if (theBoard[row][col].piece == Piece::Empty) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
      }
      else if (theBoard[row][col].pieceColour != s.pieceColour) {
        string s = " ";
        s[0] = convert(col + 1);
        s = s + to_string(row + 1);
        moves.emplace_back(s);
        break;
      }
      else {
        break;
      }
    }
  }
  return moves;
}

Colour Board::isCheckmate(Colour c) const { // is there checkmate? and returns who won if so
  if (c == Colour::Black) {
    string pos = kingLocations[1]; //black king loccation
    int kingrow = convertBackwards(pos[0]); //black king row
    int kingcol = pos[1]; //black king col
    int kingMoveSize = validMoves(theBoard[kingrow][kingcol]).size();
    if (kingMoveSize != 0) {//i.e. the black king can move
      return Colour::NoColour;
    }
    else if (theBoard[kingrow][kingcol].piece == Piece::King && theBoard[kingrow][kingcol].AttackedByWhite) {//i.e. the BLACK king is checked
      //and also has no valid moves
        if (whiteCheckLocations.size() >= 2) {//i.e. there are 2 or more piece checking the black king
          return Colour::White;
        }
        else {//black king is being checked by only one piece
          int checkingRow = convert(whiteCheckLocations[0][0]); //the row of the checking pieces
          int checkingCol = whiteCheckLocations[0][1]; //the col of the checking pieces
          Piece checkingPiece = theBoard[checkingRow][checkingCol].piece;
          //first we check if we can capture the piece
          for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
              if (theBoard[i][j].getInfo().pieceColour == Colour::Black) {
                //check valid moves that black can make to get out of check
                //in this case its just capturing the Knight
                string checklocation = whiteCheckLocations[0];
                vector<string> moves = validMoves(theBoard[i][j]);
                int numberofmoves = moves.size();
                for (int k = 0; k < numberofmoves; k++) {
                  if (moves[k] == checklocation) {//i.e. it is legal for a black piece
                    return Colour::NoColour;
                  }
                }
              }
            }
          }
          if (checkingPiece == Piece::Knight) {//if we can't capture a knight and our king has no valid moves it's checkmate
            std::cout << "Checkmated by White Knight" << std::endl;
            return Colour::White;
          }
          else if (checkingPiece == Piece::Pawn) {//if we can't capture a pawn and our king has no valid moves it's checkmate
            std::cout << "Checkmated by White Pawn" << std::endl;
            return Colour::White;
          }
          else if ((abs(kingrow-checkingRow) == 1 && abs(kingcol-checkingCol) == 0) ||
            (abs(kingrow-checkingRow) == 1 && abs(kingcol-checkingCol) == 1) ||
            (abs(kingrow-checkingRow) == 0 && abs(kingcol-checkingCol) == 1)) { //if the checking piece is adjacent
                //to the king then it's checkmate since black can't capture it and the black king has no valid moves
            return Colour::White;
          }
          else {//the checking piece is not adjacent to the black king and thus we must check for blocks
            vector<string> inbetween;
            if (checkingPiece == Piece::Rook) {
              if (checkingCol == kingcol) {//rook is in same column as king
                if (checkingRow > kingrow) {//checking piece is above the black king (fron whites perspective)
                  for (int i = kingrow+1; i < checkingRow; i++) {
                    string s = " ";
                    s[0] = convert(kingcol);
                    s = s + to_string(i);
                    inbetween.emplace_back(s);
                  }
                }
                else {
                  for (int i = checkingRow+1; i < kingrow; i++) {
                    string s = " ";
                    s[0] = convert(kingcol);
                    s = s + to_string(i);
                    inbetween.emplace_back(s);
                  }
                }
              }
              else if (checkingRow == kingrow) {//this should already be true but i'm just making sure
                if (checkingCol > kingcol) {//checking piece is above the black king (fron whites perspective)
                  for (int i = kingcol+1; i < checkingCol; i++) {
                    string s = " ";
                    s[0] = convert(kingrow);
                    s = s + to_string(i);
                    inbetween.emplace_back(s);
                  }
                }
                else {
                  for (int i = checkingCol+1; i < kingcol; i++) {
                    string s = " ";
                    s[0] = convert(kingrow);
                    s = s + to_string(i);
                    inbetween.emplace_back(s);
                  }
                }
              }
              else {
                std::cout << "something went terribly wrong in board.cc checkmate rook path" << std::endl;
              }

              int inbetweenSize = inbetween.size();
              for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                  if (theBoard[i][j].pieceColour == c) {
                    vector<string> possibleMoves = validMoves(theBoard[i][j]);
                    int MoveListSize = possibleMoves.size();
                    for (int posSize = 0; posSize < MoveListSize; posSize++) {
                      for (int trial = 0; trial < inbetweenSize; trial ++) {
                        if (possibleMoves[posSize] == inbetween[trial]) {
                          return Colour::NoColour;
                        }
                      }
                    }
                  }
                }
              }
            }
            else if (checkingPiece == Piece::Bishop) {
              int up = (kingcol - checkingCol) / abs(kingcol - checkingCol);
              int side = (kingrow - checkingRow) / abs(kingrow - checkingRow);
              int counter = checkingCol;
              for (int i = checkingRow; i != kingrow; i += side) {
                string s = " ";
                s[0] = convert(counter);
                s = s + to_string(i);
                inbetween.emplace_back(s);
                counter += up;
              }
              int inbetweenSize = inbetween.size();
              for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                  if (theBoard[i][j].pieceColour == c) {
                    vector<string> possibleMoves = validMoves(theBoard[i][j]);
                    int MoveListSize = possibleMoves.size();
                    for (int posSize = 0; posSize < MoveListSize; posSize++) {
                      for (int trial = 0; trial < inbetweenSize; trial ++) {
                        if (possibleMoves[posSize] == inbetween[trial]) {
                          return Colour::NoColour;
                        }
                      }
                    }
                  }
                }
              }
              return Colour::White;
            }

            if (checkingPiece == Piece::Queen) {
              if (kingrow == checkingRow) {

              }
              else if (kingcol == checkingCol) {

              }
              else {
                int up = (kingcol - checkingCol) / abs(kingcol - checkingCol);
                int side = (kingrow - checkingRow) / abs(kingrow - checkingRow);
                int counter = checkingCol;
                for (int i = checkingRow; i != kingrow; i += side) {
                  string s = " ";
                  s[0] = convert(counter);
                  s = s + to_string(i);
                  inbetween.emplace_back(s);
                  counter += up;
                }
                int inbetweenSize = inbetween.size();
                for (int i = 0; i < size; i++) {
                  for (int j = 0; j < size; j++) {
                    if (theBoard[i][j].pieceColour == c) {
                      vector<string> possibleMoves = validMoves(theBoard[i][j]);
                      int MoveListSize = possibleMoves.size();
                      for (int posSize = 0; posSize < MoveListSize; posSize++) {
                        for (int trial = 0; trial < inbetweenSize; trial ++) {
                          if (possibleMoves[posSize] == inbetween[trial]) {
                            return Colour::NoColour;
                          }
                        }
                      }
                    }
                  }
                }
                return Colour::White;
              }
            }
          }
        }
      }
    }
    return Colour::NoColour;
  }

 Board::~Board() {
      delete td;
      delete ob;
  }
