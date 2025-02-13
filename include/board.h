#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cctype>
#include <algorithm>
#include <utility>
#include <iostream>

#include "subject.h"
#include "square.h"

#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

// #include "move.h"

class Move;

using namespace std;

class Board : public Subject {
     protected:
          vector<vector<Square *>> the_board;
          Piece* whiteKing;
          Piece* blackKing;
     public:
          Board();
          ~Board();
          void setUp();
          void movePiece(Move& move);
          void placePiece(char piece, string position) const;
          void removePiece(string position) const;
          bool isCheck(bool isWhiteTurn) const;

          vector<Square> getPathToKing(Square &attacker_square, Square &king_square) const;
          bool isCheckmate(bool isWhiteTurn) const;
          Square& getSquare(int col, int row) const;

          void pawnGettingPromoted(bool isWhiteTurn);

          pair<vector<char>, vector<char>> getCapturedPieces() const;

          void display() const;
          bool isValidPosition(int col, int row) const; // Add this line

          bool isPresent(const vector<char> &vec, char value);

          string coordinatesToPosition(int x, int y);
};

#endif


