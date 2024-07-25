#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Board;

class Pawn : public Piece { 
     protected:
          bool first_move;

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
};

#endif
