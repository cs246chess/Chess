#include <iostream>
#include <string>
#include <ctype.h>
#include "square.h"
#include "board.h"
#include "state.h"
#include "textdisplay.h"
#include "info.h"
using namespace std;


int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Board b;
  float whiteScore = 0;
  float blackScore = 0;
  int checkturn = 0;
  try {
    while (true) {
      cin >> cmd;
      if (cin.eof()) {
        cout << "Final Score:"<< endl;
				cout << "White: " << whiteScore << endl;
				cout<< "Black: " << blackScore << endl;
				break;
      }
      if (cmd == game) {
        string p1;
        string p2;
        cin >> p1;
        cin >> p2;
        b.init();
        checkturn = 0;
      }
      else if (cmd == resign) {
        if (checkturn == 0) {
          cout << "Black wins" << endl;
        } else {
          cout << "White wins" << endl;
        }
      }
      else if (cmd == "move") {
        int move_to_row;
        char move_to_col;
        int move_from_row;
        char move_from_col;
        cin >> move_from_r  ow >> move_from_col >> move_to_row >> move_to_col;
        int colfrom = move_from_col - 'a';
        int colto = move_to_col - 'a';
        Square currentSquare = b.theBoard[colfrom][move_from_row];
        Color currentSquarecol = currentSquarecol;
        if (currentSquare.validMove(move_to_row, colto)
            && (currentSquarecol == Color::White && checkturn == 0)
            || (currentSquarecol == Color::Black && checkturn == 1)) {
          b.setPiece(move_to_row, colto, currentSquarecol, currentSquare.getInfo().piece);
          if (b.isCheckmate(currentSquarecol) == Color::Black) {
            blackScore++;
            b.init();
            checkturn = 0;
          } else if (b.isCheckmate(currentSquarecol) == Color::White) {
            whiteScore++;
            b.init();
            checkturn = 0;
          } else if (b.isStalemate(currentSquarecol)) {
            blackScore+= 0.5;
            whiteScore+= 0.5;
            b.init();
            checkturn = 0;
          } else {
            continue;
          }
          if (currentSquarecol == Color::White) {
            checkturn = 1;
          } else {
            checkturn = 0;
          }
        } else {
          cout << "Illegal Move" << endl;
          continue;
        }
      }
      else if (cmd == "setup") {
          while (true) {
            string operator;
            string p;
            b.init();
            int checkcount = 0;
            int move_to_row;
            char move_to_col;
            string colorc;
            cin >> operator;
            if (operator == "+") {
              cin >> p >> move_to_row >> move_to_col;
              int colto = move_to_col - 'a';
              if (islower(p)){
                if (p == "k") {
                  b.setPiece(move_to_row, colto, Color::Black, Piece::King);
                } else if (p == "q") {
                  b.setPiece(move_to_row, colto, Color::Black, Piece::Queen);
                } else if (p == "r") {
                  b.setPiece(move_to_row, colto, Color::Black, Piece::Rook);
                } else if (p == "b") {
                  b.setPiece(move_to_row, colto, Color::Black, Piece::Bishop);
                } else if (p == "n") {
                  b.setPiece(move_to_row, colto, Color::Black, Piece::Knight);
                } else {
                  b.setPiece(move_to_row, colto, Color::Black, Piece::Pawn);
                }
              } else {
                if (p == "K") {
                  b.setPiece(move_to_row, colto, Color::White, Piece::King);
                } else if (p == "Q") {
                  b.setPiece(move_to_row, colto, Color::White, Piece::Queen);
                } else if (p == "R") {
                  b.setPiece(move_to_row, colto, Color::White, Piece::Rook);
                } else if (p == "B") {
                  b.setPiece(move_to_row, colto, Color::White, Piece::Bishop);
                } else if (p == "N") {
                  b.setPiece(move_to_row, colto, Color::White, Piece::Knight);
                } else {
                  b.setPiece(move_to_row, colto, Color::White, Piece::Pawn);
                }
              }
            } else if (operator == "-") {
              cin >> move_to_row >> move_to_col;
              int colto = move_to_col - 'a';
              if (checkturn == 0) {
                b.setPiece(move_to_row, colto, Color::White, Piece::Empty);
              } else {
                b.setPiece(move_to_row, colto, Color::Black, Piece::Empty);
              }
            } else if (operator == "="){
              cin >> colorc;
              if (colorc == "Black") {
                checkturn = 1;
              } else {
                checkturn = 0;
              }
            } else if (operator == "done") {
              int countpawn = 0;
              for (int i = 0; i < 8; i++) {
                if (b.theBoard[0][i].getInfo().piece == Piece::Pawn || b.theBoard[8][i].getInfo().piece == Piece::Pawn) {
                  countpawn++;
                }
              }
              if (b.kingLocations.size() == 2 && countpawn == 0 && (!b.isChecked(Color::White) || !b.isChecked(Color::Black))) {
                break;
              } else {
                continue;
              }
            }
          }
      } else if (cmd == "quit") {
        break;
      }
    }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
