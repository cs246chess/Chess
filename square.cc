#include "square.h"
#include "info.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int abso(int x) {
  if (x < 0) {
    return x * -1;
  }
  return x;
}

bool Square::getAttacked(Colour c) {
  if (c == Colour::Black) {
    return this->AttackedByBlack;
  }
  else if (c == Colour::White) {
    return this->AttackedByWhite;
  }
  return false;
}

Direction getDirection(Subject<Info, State> &here, Subject<Info, State> &from) {
    Info i = from.getInfo();
    Info h = here.getInfo();
    //find the direction of the new piece
    Direction d;
    if (i.row > h.row) {//neighbour is SOUTH
        if (i.col > h.col) {//neighbour is EAST
            d = Direction::SE;
        }
        else if (i.col < h.col) {//neighbour is WEST
             d = Direction::SW;
        }
        else {//neighbour is DIRECTLY SOUTH
            d = Direction::S;
        }
    }
    else if (i.row < h.row) {//neighbour is NORTH
        if (i.col > h.col) {//neighbour is EAST
            d = Direction::NE;
        }
        else if (i.col < h.col) {//neighbour is WEST
            d = Direction::NW;
        }
        else {//neighbour is DIRECTLY NORTH
            d = Direction::N;
        }
    }
    else {//neighbour is DIRECTLY EAST or DIRECTLY WEST
        if (i.col < h.col) {//DIRECTLY WEST
            d = Direction::W;
        }
        else {//DIRECTLY EAST
            d = Direction::E;
        }
    }
    return d;
}

Square::Square(){
  AttackedByBlack = false;
  AttackedByWhite = false;
  cout << "Is this actually called?" << endl;
}

Square::Square(int r, int c, Colour colour): r{r}, c{c}, colour{colour}, piece{Piece::Empty}, pieceColour{Colour::NoColour},
  AttackedByWhite{false}, AttackedByBlack{false} {

}

void Square::setPiece(Piece p, Colour c) {    // Place a piece of given colour here.
  this->piece = p;
  this->pieceColour = c;
  State newS;
  newS.type = StateType::MovedPiece;
  newS.direction = Direction::N;
  newS.pieceColour = this->pieceColour;
  newS.piece = this->piece;
  this->setState(newS);
  this->notifyObservers();
}

bool Square::validMove(int row, int col){
  if (this->piece == Piece::Pawn) { //Pawn moves
    if (this->pieceColour == Colour::Black) {
      if (this->r - row != 1 || this->r - row != 2) {
        return false;
      } else if (this->r - row == 2) {
        if (this->r != 7) {
          return false;
        } else if (this->c - col != 0) {
          return false;
        }
      } else if (this->r - row == 1) {
        if (abso(this->c - col) > 1) {
          return false;
        }
      }
    } else if (this->pieceColour == Colour::White) {
      if (row - this->r != 1 || row - this->r != 2) {
        return false;
      } else if (row - this->r == 2) {
        if (this->r != 2) {
          return false;
        } else if (this->c - col != 0) {
          return false;
        }
      } else if (row - this->r == 1) {
        if (abso(this->c - col) > 1) {
          return false;
        }
      }
    }
  } else if (this->piece == Piece::Bishop) { //Bishop moves
    if ((abso(this->r - row) != abso(this->c - col)) || this->r - row == 0 || this->c - col == 0) {
      return false;
    }
  } else if (this->piece == Piece::Rook) { //Rook Moves
    if ((this->r - row != 0) && (this->c - col != 0)) {
      return false;
    } else if ((this->r - row == 0) && (this->c - col == 0)) {
      return false;
    }
  } else if (this->piece == Piece::Queen) { //Queen moves
    if ((abso(this->r - row) != abso(this->c - col)) && (this->r - row != 0) && (this->c - col != 0)) {
      return false;
    } else if ((this->r - row == 0) && (this->c - col == 0)) {
      return false;
    }
  } else if (this->piece == Piece::Knight) {
    if ((abso(this->r - row) == 2) && (abso(this->c - col == 1))) {
      return true;
    } else if ((abso(this->r - row) == 1) && (abso(this->c - col) == 2)) {
      return true;
    } else {
      return false;
    }
  } else if (this->piece == Piece::King) {
    if ((abso(this->r - row) > 1) && (abso(this->c - col) > 1)) {
      return false;
    } else if ((this->r - row == 0) && (this->c - col == 0)) {
      return false;
    }
  }
  return true;
}

void Square::notify(Subject<Info, State> &whoFrom) {// My neighbours will call this
  Info i = whoFrom.getInfo();
  State s = whoFrom.getState();
  //testing messages
  /*if (i.colour == Colour::Black) {
      cout << "Black Square with a ";
  }
  else if (i.colour == Colour::White) {
      cout << "White Square with a ";
  }
  else  {
      cout << "something went wrong ";
  }
  if (i.pieceColour == Colour::Black) {
      cout << "Black ";
  }
  else if (i.pieceColour == Colour::White) {
      cout << "White ";
  }
  else  {
      cout << "something went wrong ";
  }

  switch (i.piece) {
    case Piece::Knight: {
      cout << "Knight" << endl;
      break;
    }
    case Piece::Queen: {
      cout << "Queen" << endl;
      break;
    }
    case Piece::Pawn: {
      cout << "Pawn" << endl;
      break;
    }
    case Piece::Rook: {
      cout << "Rook" << endl;
      break;
    }
    case Piece::King: {
      cout << "King" << endl;
      break;
    }
    case Piece::Empty: {
      cout << "NoPiece" << endl;
      break;
    }
    default: {
      cout << "huh" << endl;
    }
  }
  cout << "carrying a message of a ";
  if (s.type == StateType::MovedPiece) {
      cout << "NewPiece.";
  }
  else if (s.type == StateType::Relay) {
      cout << "Relay.";

  }
  else  {
      cout << "Reply.";
  }

  cout << "The Square at " << i.row << " " << i.col << " called a ";
  if (colour == Colour::Black) {
      cout << "Black ";
  }
  else if (colour == Colour::White) {
      cout << "White ";
  }
  else  {
      cout << "something went wrong in notify ";
  }
  cout << "Square at " << r << " " << c << endl;
  cout << "with a ";
  if (pieceColour == Colour::Black) {
      cout << "Black ";
  }
  else if (pieceColour == Colour::White) {
      cout << "White ";
  }
  else  {
      cout << "empty square";
  }
  switch (piece) {
    case Piece::Knight: {
      cout << "Knight" << endl;
      break;
    }
    case Piece::Queen: {
      cout << "Queen" << endl;
      break;
    }
    case Piece::Pawn: {
      cout << "Pawn" << endl;
      break;
    }
    case Piece::Rook: {
      cout << "Rook" << endl;
      break;
    }
    case Piece::King: {
      cout << "King" << endl;
      break;
    }
    case Piece::Empty: {
      cout << "NoPiece" << endl;
      break;
    }
    default: {
      cout << "huh" << endl;
    }
  } */

  if (s.type == StateType::MovedPiece) {//neighbour just moved to the square, check if we need to pass more messages on
    Direction d = getDirection(*this, whoFrom);
      if (s.piece == Piece::Knight) {
      if ((d == Direction::N) || (d == Direction::W) || (d == Direction::E) || (d == Direction::S)) {
        State newS;
        newS.type = StateType::Relay;
        newS.direction = d;
        newS.pieceColour = s.pieceColour;
        newS.piece = s.piece;
        this->setState(newS);
        notifyObservers();
      }
    }
    else if (s.piece == Piece::Pawn) {
      if (((d == Direction::NE) || (d == Direction::NW)) && (s.pieceColour == Colour::White)) {
        AttackedByWhite = true;
      }
      if (((d == Direction::SE) || (d == Direction::SW)) && (s.pieceColour == Colour::Black)) {
        AttackedByBlack = true;
      }
    }
    else if (s.piece == Piece::King) {//not really needed tbh
      if (s.pieceColour == Colour::White) {
        AttackedByWhite = true;
      }
      else {
        AttackedByBlack = true;
      }
    }
    else if (s.piece == Piece::Bishop) {
      //find the direction of the new piece
      if ((d == Direction::NE) || (d == Direction::NW) || (d == Direction::SE) || (d == Direction::SW)) {
        if (s.pieceColour == Colour::Black) {
          AttackedByBlack = true;
        }
        else if (s.pieceColour == Colour::White) {
          AttackedByWhite = true;
        }
        if (piece == Piece::Empty) {
          State newS;
          newS.type = StateType::Relay;
          newS.direction = d;
          newS.pieceColour = s.pieceColour;
          newS.piece = s.piece;
          this->setState(newS);
          notifyObservers();
        }
        else {
          //do nothing
        }
      }
    }
    else if (s.piece == Piece::Rook) {
      if ((d == Direction::N) || (d == Direction::W) || (d == Direction::E) || (d == Direction::S)) {
        if (s.pieceColour == Colour::Black) {
          AttackedByBlack = true;
        }
        else if (s.pieceColour == Colour::White) {
          AttackedByWhite = true;
        }
        if (piece == Piece::Empty) {
          State newS;
          newS.type = StateType::Relay;
          newS.direction = d;
          newS.pieceColour = s.pieceColour;
          newS.piece = s.piece;
          this->setState(newS);
          notifyObservers();
        }
        else {
        //do nothing
        }
      }
    }
    else if (s.piece == Piece::Queen) {
      if (s.pieceColour == Colour::Black) {
        AttackedByBlack = true;
      }
      else if (s.pieceColour == Colour::White) {
        AttackedByWhite = true;
      }
      if (piece == Piece::Empty) {
        State newS;
        newS.type = StateType::Relay;
        newS.direction = d;
        newS.pieceColour = s.pieceColour;
        newS.piece = s.piece;
        this->setState(newS);
        notifyObservers();
      }
      else {
        //do nothing
      }
    }
    else if (s.piece == Piece::Empty) {
      State newS;
      newS.type = StateType::Relay;
      newS.direction = d;
      newS.pieceColour = s.pieceColour;
      newS.piece = s.piece;
      this->setState(newS);
      notifyObservers();
    }
  }
  else if (s.type == StateType::Relay) {
    Direction d = getDirection(*this, whoFrom);
    Direction reverse = getDirection(whoFrom, *this);
  //if the cell is in line with the direction of the relay
    //i.e. the direction of *this is the direction of the relay
    if (s.piece == Piece::Knight) {
      if (s.direction == Direction::N) {
        if ((d == Direction::NW) || (d == Direction::NE)) {
          if (s.pieceColour == Colour::Black) {
            AttackedByBlack = true;
          }
          else if (s.pieceColour == Colour::White) {
            AttackedByWhite = true;
          }
        }
      }
      else if (s.direction == Direction::S) {
        if ((d == Direction::SW) || (d == Direction::SE)) {
          if (s.pieceColour == Colour::Black) {
            AttackedByBlack = true;
          }
          else if (s.pieceColour == Colour::White) {
            AttackedByWhite = true;
          }
        }
      }
      else if ( s.direction == Direction::W) {
        if ((d == Direction::SW) || (d == Direction::NW)) {
          if (s.pieceColour == Colour::Black) {
            AttackedByBlack = true;
          }
          else if (s.pieceColour == Colour::White) {
            AttackedByWhite = true;
          }
        }
      }
      else if (s.direction == Direction::E) {
        if ((d == Direction::NE) || (d == Direction::SE)) {
          if (s.pieceColour == Colour::Black) {
            AttackedByBlack = true;
          }
          else if (s.pieceColour == Colour::White) {
            AttackedByWhite = true;
          }
        }
      }
    }
    else if (s.direction == d) {
      //even if there is a piece, the square is still under attack by the
      // piece who is sending the notification
      if (s.pieceColour == Colour::Black) {
        AttackedByBlack = true;
      }
      else if (s.pieceColour == Colour::White) {
        AttackedByWhite = true;
      }
      if (piece != Piece::Empty) {
        if (piece == Piece::Pawn) {
          //do nothing
        }
        //Bishop may be able to attack more squares, so reply is needed
        if (piece == Piece::Bishop) {
          if ((reverse == Direction::NW) || (reverse == Direction::NE) || (reverse == Direction::SE) || (reverse == Direction::SW)) {
            State newS;
            newS.type = StateType::Reply;
            newS.piece = this->piece;
            newS.direction = reverse;
            newS.pieceColour = pieceColour;
            this->setState(newS);
            notifyObservers();
          }
        }
        //king follows the same idea as the pawn, so no need to
        // recalculate the king's squares it is attacking
        if (piece == Piece::King) {
          //do nothing
        }
        //Queen may be able to attack more squares than before
        if (piece == Piece::Queen) {
          State newS;
          newS.type = StateType::Reply;
          newS.direction = reverse;
          newS.piece = this->piece;
          newS.pieceColour = pieceColour;
          this->setState(newS);
          notifyObservers();
        }
        //Rook may be able to attack more squares than before
        if (piece == Piece::Rook) {
          if ((reverse == Direction::S) || (reverse == Direction::N) || (reverse == Direction::E) || (reverse == Direction::W)) {
            State newS;
            newS.type = StateType::Reply;
            newS.direction = reverse;
            newS.piece = this->piece;
            newS.pieceColour = pieceColour;
            this->setState(newS);
            notifyObservers();
          }
          }
        }
        else {    //no piece located so it just continues the relay
          State newS;
          newS.type = StateType::Relay;
          newS.direction = s.direction;
          newS.pieceColour = s.pieceColour;
          this->setState(newS);
          notifyObservers();
        }
      }
    }
    else { //type is a reply to check for discovered checks
      Direction d = getDirection(*this, whoFrom);
      Direction reverse = getDirection(whoFrom, *this);
      //if the cell is in line with the direction of the relay
      //i.e. the direction of *this is the direction of the relay
      if (s.pieceColour == Colour::Black) {
        AttackedByBlack = true;
      }
      else if (s.pieceColour == Colour::White) {
        AttackedByWhite = true;
      }
      if (piece != Piece::Empty) {
        //already calculated so nothing needs to happen
      }
    else {    //no piece located so it just continues the reply
        State newS;
        newS.type = StateType::Reply;
        newS.direction = s.direction;
        newS.pieceColour = s.pieceColour;
        this->setState(newS);
        notifyObservers();
    }
  }
}

Info Square::getInfo() const {
  Info i = {r, c, colour, piece, pieceColour};
  return i;
}

ostream &operator<<(ostream &out, const Square &sq) {
  out << "Row: " << sq.r << endl;
  out << "Column: " << sq.c << endl;
  switch (sq.piece) {
    case Piece::Knight: {
      out << "Knight" << endl;
      break;
    }
    case Piece::Queen: {
      out << "Queen" << endl;
      break;
    }
    case Piece::Pawn: {
      out << "Pawn" << endl;
      break;
    }
    case Piece::Rook: {
      out << "Rook" << endl;
      break;
    }
    case Piece::King: {
      out << "King" << endl;
      break;
    }
    case Piece::Empty: {
      out << "NoPiece" << endl;
      break;
    }
    default: {
      out << "huh" << endl;
    }
  }
  switch (sq.colour) {
    case Colour::Black:
      out << "Black Square" << endl;
      break;
    case Colour::White:
      out << "White Square" << endl;
      break;
    default:
      out << "No colour square????" << endl;
  }
  switch (sq.pieceColour) {
    case Colour::Black: {
      out << "Black Piece" << endl;
      break;
    }
    case Colour::White: {
      out << "White Piece" << endl;
      break;
    }
    default: {
      out << "No piece/no colour piece" << endl;
    }
  }
  if (sq.AttackedByBlack) {
    out << "Square attacked by Black" << endl;
  }
  if (sq.AttackedByWhite) {
    out << "Square attacked by White" << endl;
  }
  return out;
}
