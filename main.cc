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
  b.kingLocations.push_back("");
  b.kingLocations.push_back("");
  float whiteScore = 0; // keeps track of score of white set
  float blackScore = 0; // keeps track of score of black set
  int checkturn = 0; // to keep track of users turns 0 = white 1 = black
  //GraphicsDisplay * screen = nullptr;
  try {
    while (true) {
      cin >> cmd;
      if (cin.eof()) {
        cout << "Final Score:"<< endl;
				cout << "White: " << whiteScore << endl;
				cout << "Black: " << blackScore << endl;
				break;
      }
      if (cmd == "game") { // initiates the chess board
        string p1; // player1
        string p2; // player2
        cin >> p1;
        cin >> p2;
        //GraphicsDisplay * temp = screen;
        //delete temp;
        //screen = new GraphicsDisplay();
        b.init();
        for (int i = 0; i <8; i++) { // sets the initial pieces on the board when the game starts
          b.setPiece(6, i, Colour::Black, Piece::Pawn);
          b.setPiece(1, i, Colour::White, Piece::Pawn);
        }
        b.setPiece(7, 0, Colour::Black, Piece::Rook);
        b.setPiece(7, 1, Colour::Black, Piece::Knight);
        b.setPiece(7, 2, Colour::Black, Piece::Bishop);
        b.setPiece(7, 3, Colour::Black, Piece::Queen);
        b.setPiece(7, 4, Colour::Black, Piece::King);
        b.setPiece(7, 5, Colour::Black, Piece::Bishop);
        b.setPiece(7, 6, Colour::Black, Piece::Knight);
        b.setPiece(7, 7, Colour::Black, Piece::Rook);
        b.setPiece(0, 0, Colour::White, Piece::Rook);
        b.setPiece(0, 1, Colour::White, Piece::Knight);
        b.setPiece(0, 2, Colour::White, Piece::Bishop);
        b.setPiece(0, 3, Colour::White, Piece::Queen);
        b.setPiece(0, 4, Colour::White, Piece::King);
        b.setPiece(0, 5, Colour::White, Piece::Bishop);
        b.setPiece(0, 6, Colour::White, Piece::Knight);
        b.setPiece(0, 7, Colour::White, Piece::Rook);
        checkturn = 0;
        cout << b << endl;
      }
      else if (cmd == "resign") { // player forfeits the match and the win goes to the opponent
        if (checkturn == 0) {
          cout << "Black wins" << endl;
        } else {
          cout << "White wins" << endl;
        }
      }
      else if (cmd == "move") { // command to place chess pieces during the game
        int move_to_row; // row to move piece to
        char move_to_col; // column to move piece to
        int move_from_row; // stores the row the piece currently is in
        char move_from_col; // stores the column the piece currently is in
        cin >> move_from_row >> move_from_col >> move_to_row >> move_to_col;
        int colfrom = move_from_col - 'a'; // converts col from char to int
        int colto = move_to_col - 'a'; // converts col to from char to int
        Square currentSquare = b.theBoard[colfrom][move_from_row];
        Colour currentSquarecol = currentSquare.getInfo().colour;
	      int inlist = 0; // no of possible moves in validMoves
        int posMoveSize = b.validMoves(currentSquare).size();
	      for (int i = 0; i < posMoveSize ; i++) {
		        string row = to_string(move_to_row);
		        string col = to_string(move_to_col);
		        string rowcol = row + col; // concatenates to check for rowcol in validMoves
		        if (rowcol == b.validMoves(currentSquare)[i]) { // check to see if the move is valid
			           inlist++;
		        } else {
			           inlist+=0;
		        }
	      }
        if ((inlist > 0
            && (currentSquarecol == Colour::White && checkturn == 0)) // check to see if the piece
                                                                      //being moved is consistent with players turn
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
          if (b.isCheckmate(currentSquarecol) == Colour::Black) { // checks for checkmate and adds score to the player
            blackScore++;
            b.init();
            checkturn = 0;
          } else if (b.isCheckmate(currentSquarecol) == Colour::White) { // checks for checkmate and adds score to the player
            whiteScore++;
            b.init();
            checkturn = 0;
          } else if (b.isStalemate(currentSquarecol)) { //checks for stalemate and adds half a point to each player
            blackScore+= 0.5;
            whiteScore+= 0.5;
            b.init();
            checkturn = 0;
          } else {
            continue;
          }
          if (currentSquarecol == Colour::White) { // swtiches turn after a move is made
            checkturn = 1;
          } else {
            checkturn = 0;
          }
        } else {
          cout << "Illegal Move" << endl; // error message
          continue;
        }
        cout << b << endl;
      }
      else if (cmd == "setup") { // allows the player to set pieces on board before starting game
        b.init();
          while (true) {
            string op;
            string p;
            cout << b << endl;
            int move_to_row;
            int move_to_col;
            string colorc;
            cin >> op;
            if (op == "+") { // reads a piece and a square location to set it on the board
              cin >> p;
              cin >> op;
              move_to_row = op[1] - '0';
              move_to_col = (convertBackwards(op[0]));
              int colto = move_to_col;
              if (p == "k") {
                if (b.kingLocations[1] == "") {//adding black king location to board
                    b.setPiece(move_to_row, colto, Colour::Black, Piece::King);
                    b.kingLocations[1] = op;
                  }
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
        } else if (p == "K") {//adding white king location to board
                if (b.kingLocations[0] == "") {
                    b.setPiece(move_to_row, colto, Colour::White, Piece::King);
                    b.kingLocations[0] = op;
                  }
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

      } else if (op == "-") { // removes a set piece from the board and replaces it with an empty piece
        cin >> op;
        move_to_row = op[1] - '0';
        move_to_col = (convertBackwards(op[0]));
        int colto = move_to_col;
        Piece isKing = b.theBoard[move_to_row - 1][colto - 1].piece;
        if (isKing == Piece::King) {//removing king location from board
          if (b.theBoard[move_to_row - 1][colto - 1].pieceColour == Colour::White) {
            b.kingLocations[0] = "";
          } else {
            b.kingLocations[1] = "";
          }
        }
        b.setPiece(move_to_row, colto, Colour::NoColour, Piece::Empty);
        cout << b << endl;
            } else if (op == "="){ // switches users turn to the opponent
              cin >> colorc;
              if (colorc == "Black") {
                checkturn = 1;
              } else {
                checkturn = 0;
              }
            } else if (op == "done") { // user leaves setup mode if all conditions are met
              int countpawn = 0;
              for (int i = 0; i < 8; i++) {
                if (b.theBoard[0][i].getInfo().piece == Piece::Pawn || b.theBoard[7][i].getInfo().piece == Piece::Pawn) {
                  countpawn++;
                }
              }
              if (b.kingLocations[0] != "" && b.kingLocations[1] != "" && countpawn == 0 && (!b.isChecked(Colour::White) || !b.isChecked(Colour::Black))) {
                break;
              } else {
                cout << "Conditions to leave setup not met" << endl; // error message
                continue;
              }
            }
          }
      } else if (cmd == "quit") { // to break out of the game
        break;
      }
    }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
