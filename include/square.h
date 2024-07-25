#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <string>

class Piece;
class Board;

// #include "piece.h"
#include <utility>


using namespace std;

class Square {
     protected:
          int col;
          int row;
          Piece* the_piece;

     public:
          Square(int col, int row, Piece* the_piece);
          Square(int col, int row);
          Square(const string& position, const Board& board);
          ~Square();

          bool isOccupied();

          Piece* getPiece();

          void setPiece(Piece* new_piece);

          void removePiece();

          pair<int, int> getCoordinates() const;

          bool operator==(Square& rhs);
};

#endif
