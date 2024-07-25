#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "square.h"
#include "board.h"
#include "piece.h"

// class Piece;

using namespace std;

class Move {
private:
    Square* from;
    Square* to;
    Piece* piece;
    const Board& board;


public:
    // Constructors
    Move(Square* from, Square* to, Piece* piece, const Board& board);
    
    // Destructor
    ~Move();
    
    // Accessors
    Square* getStartingCoord() const { return from; }
    Square* getDestinationCoord() const { return to; }
    Piece* getPiece() const { return piece; }
    
    // Mutators
    void setPiece(Piece* p) { piece = p; }
};

#endif // MOVE_H_
