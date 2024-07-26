// #ifndef PAWN_H
// #define PAWN_H
// #include "piece.h"

// class Board;

// class Pawn : public Piece { 
//      protected:
//           bool first_move;

//      public:
//           Pawn(Square *current_position, const string& colour, const char symbol);
//           ~Pawn() override{};
//           void move(Square *new_position, const Board &the_board) override;
//           char getSymbol() const override;
//           bool validMove(Square &new_position, const Board &the_board) override;

//           void setFirstMove(bool status) override {
//                first_move = status;
//           }

//           vector<Square> getPossibleMoves(const Board &the_board);
// };

// #endif

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Board;
class Game;

class Pawn : public Piece { 
     protected:
          bool first_move;
          bool moved_two_squares;
          int move_counter;

     public:
          Pawn(Square *current_position, const string& colour, const char symbol);
          ~Pawn() override{};
          void move(Square *new_position, const Board &the_board) override;
          char getSymbol() const override;
          bool validMove(Square &new_position, const Board &the_board) override;

          void setFirstMove(bool status) override {
               first_move = status;
          }

          vector<Square> getPossibleMoves(const Board &the_board);

          Square* isCurrentMoveEnPassant(pair<int, int> old_position, Square& new_position, const Board& the_board);
};

#endif
