#include "square.h"
#include <vector>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::string;

int abs(int x) {
  if (x < 0) {
    return x * -1;
  }
  return x;
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

Square(int r, int c, Colour colour) {


Square(int r, int c, Color colour) {
  this->r = r;
  this->c = c;
  this->colour = colour;
  p = Piece::Empty;
  pColour = Color::NoColour;

}

void Square::Square::setPiece(Piece p, Colour colour, Colour c) {    // Place a piece of given colour here.
  this->p = p;
  this->pieceColour = c;
}
void Square::validMove(int row, int col){
  if (this->p == Piece::Pawn) { //Pawn moves
    if (this->pieceColour == Color::Black) {
      if (this->r - row != 1 || this->r - row != 2) {
        return false;
      } else if (this->r - row == 2) {
        if (this->r != 7) {
          return false;
        } else if (this->c - col != 0) {
          return false;
        }
      } else if (this->r - row == 1) {
        if (abs(this->c - col) > 1) {
          return false;
        }
      }
    } else if if (this->pieceColour == Color::white) {
      if (row - this->r != 1 || row - this->r != 2) {
        return false;
      } else if (row - this->r == 2) {
        if (this->r != 2) {
          return false;
        } else if (this->c - col != 0) {
          return false;
        }
      } else if (row - this->r == 1) {
        if (abs(this->c - col) > 1) {
          return false;
        }
      }
    }
  } else if (this->p == Piece::Bishop) { //Bishop moves
    if ((abs(this->r - row) != abs(this->c - col)) || this->r - row == 0 || this->c - col == 0) {
      return false;
    }
  } else if (this->p == Piece::Rook) { //Rook Moves
    if ((this->r - row != 0) && (this->c - col != 0)) {
      return false;
    } else if ((this->r - row == 0) && (this->c - col == 0)) {
      return false;
    }
  } else if (this->p == Piece::Queen) { //Queen moves
    if ((abs(this->r - row) != abs(this->c - col)) && (this->r - row != 0) && (this->c - col != 0)) {
      return false;
    } else if ((this->r - row == 0) && (this->c - col == 0)) {
      return false;
    }
  } else if (this->p == Piece::Knight) {
    if ((abs(this->r - row) == 2) && (abs(this->c - col == 1))) {
      return true;
    } else if ((abs(this->r - row) == 1) && (abs(this->c - col) == 2)) {
      return true;
    } else {
      return false;
    }
  } else if (this->p == Piece::King) {
    if ((abs(this->r - row) > 1) && (abs(this->c - col) > 1)) {
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
  /*if (i.colour == Colour::NoColour) {
      cout << "Empty ";
  }
  else if (i.colour == Colour::White) {
      cout << "White ";
  }
  else  {
      cout << "Black ";
  }

  if (s.type == StateType::NewPiece) {
      cout << "NewPiece ";
  }
  else if (s.type == StateType::Relay) {
      cout << "Relay ";
  }
  else  {
      cout << "Reply ";
  }
  cout << "Cell at " << i.row << " " << i.col << " called ";
  if (colour == Colour::NoColour) {
      cout << "Empty ";
  }
  else if (colour == Colour::White) {
      cout << "White ";
  }
  else  {
      cout << "Black ";
  }
  cout << "Cell at " << r << " " << c << endl;
  */
  if (s.type == StateType::MovedPiece) {//neighbour just moved to the square, check if we need to pass more messages on
    switch(s.piece) {
      case Piece::Knight:
      Direction d = getDirection(*this, whoFrom);
      if ((d == Direction::N) || (d == Direction::W) || (d == Direction::E) || (d == Direction::S)) {
        State newS;
        newS.type = StateType::Relay;
        newS.direction = d;
        newS.pieceColour = s.pieceColour;
        newS.piece = s.piece
        this->setState(newS);
        notifyObservers();
      }
        break;
      case Piece::Pawn:
      Direction d = getDirection(*this, whoFrom);
      if (((d == Direction::NE) || (d == Direction::NW)) && (s.pieceColour == Color::White) {
        State newS;
        newS.type = StateType::Relay;
        newS.direction = d;
        newS.pieceColour = s.pieceColour;
        newS.piece = s.piece
        this->setState(newS);
        notifyObservers();
      }
      if (((d == Direction::SE) || (d == Direction::SW)) && (s.pieceColour == Color::Black) {
        State newS;
        newS.type = StateType::Relay;
        newS.direction = d;
        newS.pieceColour = s.pieceColour;
        newS.piece = s.piece
        this->setState(newS);
        notifyObservers();
      }
        break;
      case Piece::King:
        Direction d = getDirection(*this, whoFrom);
        State newS;
        newS.type = StateType::Relay;
        newS.direction = d;
        newS.pieceColour = s.pieceColour;
        newS.piece = s.piece;
        this->setState(newS);
        notifyObservers();
        break;
      case Piece::Bishop:
        //find the direction of the new piece
        Direction d = getDirection(*this, whoFrom);
        if ((d == Direction::NE) || (d == Direction::NW) || (d == Direction::SE) || (d == Direction::SW)) {
          State newS;
          newS.type = StateType::Relay;
          newS.direction = d;
          newS.pieceColour = s.pieceColour;
          newS.piece = s.piece
          this->setState(newS);
          notifyObservers();
        }
        break;
      case Piece::Rook:
      Direction d = getDirection(*this, whoFrom);
      if ((d == Direction::N) || (d == Direction::W) || (d == Direction::E) || (d == Direction::S)) {
        State newS;
        newS.type = StateType::Relay;
        newS.direction = d;
        newS.pieceColour = s.pieceColour;
        newS.piece = s.piece
        this->setState(newS);
        notifyObservers();
      }
        break;
      case Piece::Queen:
        Direction d = getDirection(*this, whoFrom);
        State newS;
        newS.type = StateType::Relay;
        newS.direction = d;
        newS.pieceColour = s.pieceColour;
        newS.piece = s.piece;
        this->setState(newS);
        notifyObservers();
        break;
    }
  }
  else if (s.type == StateType::Relay) {
      Direction d = getDirection(*this, whoFrom);
      Direction reverse = getDirection(whoFrom, *this);
      //if the cell is in line with the direction of the relay
      //i.e. the direction of *this is the direction of the relay
      if (s.piece == Piece::Knight) {
        if (s.direction == Direction::N) {}
          if ((d == Direction::NW) || (d == Direction::NE)) {
            State newS;
            newS.type = StateType::Relay;
            newS.direction = d;
            newS.pieceColour = s.pieceColour;
            this->setState(newS);
            notifyObservers();
          }
        }
        else if ( s.direction == Direction::S) {
          if ((d == Direction::SW) || (d == Direction::SE)) {
            State newS;
            newS.type = StateType::Relay;
            newS.direction = d;
            newS.colour = s.colour;
            this->setState(newS);
            notifyObservers();
          }
        }
        else if ( s.direction == Direction::W) {
          if ((d == Direction::SW) || (d == Direction::NW)) {
            State newS;
            newS.type = StateType::Relay;
            newS.direction = d;
            newS.colour = s.colour;
            this->setState(newS);
            notifyObservers();
          }
        }
        else if (s.direction == Direction::E) {
          if ((d == Direction::NE) || (d == Direction::SE)) {
            State newS;
            newS.type = StateType::Relay;
            newS.direction = d;
            newS.colour = s.colour;
            this->setState(newS);
            notifyObservers();
          }
        }
        else {
          if (piece != Empty) {
            if (pieceColour == s.pieceColour) {
              //do nothing
            }
            else {
              State newS;
              newS.type = StateType::Reply;
              newS.direction = reverse;
              newS.pieceColour = pieceColour;
              this->setState(newS);
              notifyObservers();
            }
          }
        }
      }
      else if (s.direction == d) {
          if (piece != Empty) {
            if (pieceColour == s.pieceColour) {
              //do nothing
            }
            else { //other colour
              swtich(piece) {
                case Piece::Pawn:
                break;
                case Piece::Bishop:
                if ((d == NE) || (d == SW) || (d == SE) || (d == NW)) {
                  State newS;
                  newS.type = StateType::Reply;
                  newS.direction = reverse;
                  newS.pieceColour = pieceColour;
                  this->setState(newS);
                  notifyObservers();
                }
                break;
                case Piece::King:
                if (i.piece == Piece::King) {
                  State newS;
                  newS.type = StateType::Reply;
                  newS.direction = reverse;
                  newS.pieceColour = pieceColour;
                  this->setState(newS);
                  notifyObservers();
                }
                else if (i.piece == Piece::Pawn) {
                  check = true;
                }
                break;
                case Piece::Queen:
                State newS;
                newS.type = StateType::Reply;
                newS.direction = reverse;
                newS.pieceColour = pieceColour;
                this->setState(newS);
                notifyObservers();
                break;
                case Piece::Rook:
                if ((d == N) || (d == S) || (d == E) || (d == W)) {
                  State newS;
                  newS.type = StateType::Reply;
                  newS.direction = reverse;
                  newS.pieceColour = pieceColour;
                  this->setState(newS);
                  notifyObservers();
                }
                break;
              }
            }
          }
          else {    //the current cell's colour doesnt match the new piece's colour so its a relay
              State newS;
              newS.type = StateType::Relay;
              newS.direction = s.direction;
              newS.colour = s.colour;
              this->setState(newS);
              notifyObservers();
          }
      }
      else {
          //do nothing because the current cell
          //is not in line with the current line check
      }
  }
  else if (s.type == StateType::Relay) {
      Direction d = getDirection(*this, whoFrom);
      //if the cell is in line with the direction of the relay
      //i.e. the direction of *this is the direction of the relay
      if (s.direction == d) {
          if (s.colour == colour) {
              //if the colour of the new piece matches the current
              //cell's colour then the current cell is a reply
              State newS;
              newS.type = StateType::Reply;
              newS.direction = s.direction;
              newS.colour = s.colour;
              this->setState(newS);
              notifyObservers();
          }
          else {    //the current cell's colour doesnt match the new piece's colour so its a relay
              State newS;
              newS.type = StateType::Relay;
              newS.direction = s.direction;
              newS.colour = s.colour;
              this->setState(newS);
              notifyObservers();
          }
      }
      else {
          //do nothing because the current cell
          //is not in line with the current line check
      }
  }
  if (piece == Piece::NoPiece) {

  }
  else if (s.pieceColour == pieceColour) {
    if (s.piece == Piece::Knight) {

    }
  }
  else {//opposite colour


  }
  //get states and info from neighbour that called notify

  //if the neighbour is a new piece we check its colour, and set our state
  //accordingly then pass the message down if necessary
    else {
        //cout << "HAS A COLOUR" << endl;
        if (s.type == StateType::NewPiece) {
        //find the direction of the new piece
            Direction d = getDirection(*this, whoFrom);
            if (s.colour == colour) {}
                //if the colour is the same as the new piece
                //we dont have to do anything
            else {//the new neighbouring piece is of opposite colour
                State newS;
                newS.type = StateType::Relay;
                newS.direction = d;
                newS.colour = i.colour;
                this->setState(newS);
                notifyObservers();
            }
        }

        else { //notified by reply so we should check to see if we need to change colours
            //cout << "REPLY" << endl;
            Direction d = getDirection(whoFrom, *this); //this is the opposite direction we previously found
            //basically check to see if the current cell is between the reply and the new piece
            if (s.direction == d) {
                if (s.colour == colour) {//we have (presumably) arrived back at the new piece
                    //cout << "NOTIFIED BY SAME COLOUR REPLY" << endl;
                    //we don't need to do anything to the new piece
                }
                else {//colour of the cell does not match the colour of the new piece AND has been notified by a reply
                //we therefore need to update its colour and make the cell a reply and then notify its neighbours
                    //cout << "FLIP THIS" << endl;
                    this->toggle();//update colour
                    State newS;
                    newS.type = StateType::Reply;
                    newS.direction = s.direction;
                    newS.colour = s.colour;
                    this->setState(newS);
                    notifyObservers();
                }
            }
            else {
                //do nothing because the current cell
                //is not in line with the current reply/newpiece
            }
        }
    }
}


Info getInfo() const {
  return Info{r, c, colour, p};
}
