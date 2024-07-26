#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "square.h"
// #include "board.h"
#include "piece.h"

// class Piece;

class Board;

using namespace std;

class Move {
private:
    Square* from;
    Square* to;
    pair<int, int> from_coordinates;
    pair<int, int> to_coordinates;
    Piece* piece;
    const Board& board;

public:
    // Default constructor
    // Move(const Board& board) : from(nullptr), to(nullptr), piece(nullptr), board(board) {}

    // Parameterized constructor
    Move(Square* from, Square* to, Piece* piece, const Board& board)
        : from(from), to(to), piece(piece), board(board) {}

    Move(pair<int, int> from_coordinates, pair<int, int> to_coordinates, Piece* piece, const Board& board)
        : from_coordinates(from_coordinates), to_coordinates(to_coordinates), piece(piece), board(board) 
    {
        from = nullptr;
        to = nullptr;
    }

    // Destructor
    ~Move() {}

    // Copy constructor
    Move(const Move& other)
        : from(other.from), to(other.to), from_coordinates(other.from_coordinates),
          to_coordinates(other.to_coordinates), piece(other.piece), board(other.board) {}

    // Copy assignment operator
    Move& operator=(const Move& other) {
        if (this == &other) {
            return *this; // Handle self-assignment
        }
        from = other.from;
        to = other.to;
        from_coordinates = other.from_coordinates;
        to_coordinates = other.to_coordinates;
        piece = other.piece;
        // `board` is a const reference, it should not be reassigned
        return *this;
    }

    // Move constructor
    Move(Move&& other) noexcept
        : from(other.from), to(other.to), from_coordinates(move(other.from_coordinates)),
          to_coordinates(move(other.to_coordinates)), piece(other.piece), board(other.board) {
        other.from = nullptr;
        other.to = nullptr;
        other.piece = nullptr;
    }

    // Move assignment operator
    Move& operator=(Move&& other) noexcept {
        if (this == &other) {
            return *this; // Handle self-assignment
        }
        from = other.from;
        to = other.to;
        from_coordinates = move(other.from_coordinates);
        to_coordinates = move(other.to_coordinates);
        piece = other.piece;
        // `board` is a const reference, it should not be reassigned

        other.from = nullptr;
        other.to = nullptr;
        other.piece = nullptr;
        return *this;
    }

    // Accessors
    Square* getStartingCoord() const { return from; }
    Square* getDestinationCoord() const { return to; }
    Piece* getPiece() const { return piece; }

    pair<int, int> getFromCoordinates() const { return from_coordinates; }
    pair<int, int> getToCoordinates() const { return to_coordinates; }
    
    // Mutators
    void setPiece(Piece* p) { piece = p; }
};

#endif // MOVE_H_
