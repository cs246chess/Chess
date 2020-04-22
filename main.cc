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
  GraphicsDisplay * screen = nullptr;
  try {
    while (true) {
      cin >> cmd;
      if (cin.eof()) {
        cout << "Final Score:"<< endl;
				cout << "White: " << whiteScore << endl;
				cout << "Black: " << blackScore << endl;
				break;
      }
      if (cmd == "game") {
        string p1;
        string p2;
        cin >> p1;
        cin >> p2;
        GraphicsDisplay * temp = screen;
        delete temp;
        screen = new GraphicsDisplay();
        b.init();
        checkturn = 0;
        cout << b << endl;
      }
      else if (cmd == "resign") {
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
        cin >> move_from_row >> move_from_col >> move_to_row >> move_to_col;
        int colfrom = move_from_col - 'a';
        int colto = move_to_col - 'a';
        Square currentSquare = b.theBoard[colfrom][move_from_row];
        Colour currentSquarecol = currentSquare.getInfo().colour;
	int inlist = 0;
  int posMoveSize = b.validMoves(currentSquare).size();
	for (int i = 0; i < posMoveSize ; i++) {
		string row = to_string(move_to_row);
		string col = to_string(move_to_col);
		string rowcol = row + col;
		if (rowcol == b.validMoves(currentSquare)[i]) {
			inlist++;
		} else {
			inlist+=0;
		}
	}
        if ((inlist > 0
            && (currentSquarecol == Colour::White && checkturn == 0))
            || (currentSquarecol == Colour::Black && checkturn == 1)) {
          b.setPiece(move_to_row, colto, currentSquarecol, currentSquare.getInfo().piece);
          b.setPiece(move_from_row, colfrom, Colour::NoColour, Piece::Empty);
          string row = to_string(move_to_row);
      		string col = to_string(move_to_col);
          string rowprev = to_string(move_from_col);
          string colprev = to_string(move_from_col);
          string last_move = colprev + rowprev + row + col;
          b.lastMove = last_move;
          if (currentSquare.getInfo().piece == Piece::King) {
            if (currentSquare.getInfo().pieceColour == Colour::White) {
              b.hasWhiteKingMoved = true;
            }
            else if (currentSquare.getInfo().pieceColour == Colour::Black) {
              b.hasBlackKingMoved = true;
            }
          }
          else if ((currentSquare.getInfo().piece == Piece::Rook) && (move_from_col == 'a')) {
            if (currentSquare.getInfo().pieceColour == Colour::White) {
              b.hasWhiteRookAMoved = true;
            }
            else if (currentSquare.getInfo().pieceColour == Colour::Black) {
              b.hasBlackRookAMoved = true;
            }
          }
          else if ((currentSquare.getInfo().piece == Piece::Rook) && (move_from_col == 'h')) {
            if (currentSquare.getInfo().pieceColour == Colour::White) {
              b.hasWhiteRookHMoved = true;
            }
            else if (currentSquare.getInfo().pieceColour == Colour::Black) {
              b.hasBlackRookHMoved = true;
            }
          }
          if (b.isCheckmate(currentSquarecol) == Colour::Black) {
            blackScore++;
            b.init();
            checkturn = 0;
          } else if (b.isCheckmate(currentSquarecol) == Colour::White) {
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
          if (currentSquarecol == Colour::White) {
            checkturn = 1;
          } else {
            checkturn = 0;
          }
        } else {
          cout << "Illegal Move" << endl;
          continue;
        }
        cout << b << endl;
      }
      else if (cmd == "setup") {
          while (true) {
            string op;
            string p;
            b.init();
            cout << b << endl;
            int move_to_row;
            char move_to_col;
            string colorc;
            cin >> op;
            if (op == "+") {
              cin >> p;
              cin >> op;
              move_to_row = op[1];
              move_to_col = convertBackwards(op[0]);
              int colto = move_to_col - 'a';
              if (p == "k") {
		      b.setPiece(move_to_row, colto, Colour::Black, Piece::King);
              } else if (p == "q") {
                      b.setPiece(move_to_row, colto, Colour::Black, Piece::Queen);
              } else if (p == "r") {
                      b.setPiece(move_to_row, colto, Colour::Black, Piece::Rook);
              } else if (p == "b") {
		      b.setPiece(move_to_row, colto, Colour::Black, Piece::Bishop);
              } else if (p == "n") {
		      b.setPiece(move_to_row, colto, Colour::Black, Piece::Knight);
              } else if (p == "p") {
		      b.setPiece(move_to_row, colto, Colour::Black, Piece::Pawn);
              } else if (p == "K") {
                      b.setPiece(move_to_row, colto, Colour::White, Piece::King);
              } else if (p == "Q") {
                      b.setPiece(move_to_row, colto, Colour::White, Piece::Queen);
              } else if (p == "R") {
                      b.setPiece(move_to_row, colto, Colour::White, Piece::Rook);
              } else if (p == "B") {
                      b.setPiece(move_to_row, colto, Colour::White, Piece::Bishop);
              } else if (p == "N") {
                      b.setPiece(move_to_row, colto, Colour::White, Piece::Knight);
              } else {
                      b.setPiece(move_to_row, colto, Colour::White, Piece::Pawn);
              }
	      cout << b << endl;

            } else if (op == "-") {
              cin >> move_to_row >> move_to_col;
              int colto = move_to_col - 'a';
              if (checkturn == 0) {
                b.setPiece(move_to_row, colto, Colour::White, Piece::Empty);
              } else {
                b.setPiece(move_to_row, colto, Colour::Black, Piece::Empty);
              }
              cout << b << endl;
            } else if (op == "="){
              cin >> colorc;
              if (colorc == "Black") {
                checkturn = 1;
              } else {
                checkturn = 0;
              }
            } else if (op == "done") {
              int countpawn = 0;
              for (int i = 0; i < 8; i++) {
                if (b.theBoard[0][i].getInfo().piece == Piece::Pawn || b.theBoard[8][i].getInfo().piece == Piece::Pawn) {
                  countpawn++;
                }
              }
              if (b.kingLocations.size() == 2 && countpawn == 0 && (!b.isChecked(Colour::White) || !b.isChecked(Colour::Black))) {
                break;
              } else {
                cout << "Conditions to leave setup not met" << endl;
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
