#ifndef STATE_H
#define STATE_H

/* State types are:
    Moved Piece: I am a piece that was just moved. I'm letting you know that I exist,
    in case you need to calculate checks or stalemates

    Relay -- I am empty.  I am simply carrying a message forward

    Reply -- I am not empty.   I have a piece in a straight line from me,
    that is not of my colour, and that currently influences me.
      *same colour replies are redundant and are not necessary.
*/

enum Class Piece { Pawn, Rook, King, Bishop, Knight, Queen, Empty};
enum class StateType { MovedPiece, Relay, Reply };
enum class Colour { NoColour, Black, White };
enum class Direction { NW, N, NE, W, E, SW, S, SE };

//1. knight notifies neighbours
//2. neighbours get the message direction, if they're not n/w/s/e they discard it and th en they notify
//3. neighbours of neigjhbours get message.  e.g. message went west -> i am north west of who notified me -> is this check/this square is influenced
struct State {
  Piece piece; //what was the piece? (not what piece am I)
  StateType type;  // See above
  Colour colour;   // What colour was the piece?  (NOT what is my colour)
  Direction direction;  // In which direction from me is the piece?
};

#endif
