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

    pair<int, int> from_coordinates;
    pair<int, int> to_coordinates;

public:
    // Constructors
    Move(Square* from, Square* to, Piece* piece, const Board& board);

    Move(pair<int, int> from_coordinates, pair<int, int> to_coordinates, Piece *piece, const Board &board)
        : from_coordinates{from_coordinates}, to_coordinates{to_coordinates}, piece{piece}, board{board} 
        {
            from = nullptr;
            to = nullptr;
    }

    // Destructor
    ~Move();

    // Accessors
    Square* getStartingCoord() const { return from; }
    Square* getDestinationCoord() const { return to; }
    Piece* getPiece() const { return piece; }

    pair<int, int> getFromCoordinates() { return from_coordinates; }
    pair<int, int> getToCoordinates() { return to_coordinates; }
    
    // Mutators
    void setPiece(Piece* p) { piece = p; }
};

#endif // MOVE_H_
