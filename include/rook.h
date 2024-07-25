#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece { 
     protected:
          bool first_move;

     public:
          Rook(Square *current_position, const string& colour, const char symbol);
          ~Rook() override{};
          void move(Square *new_position, const Board &the_board) override;
          char getSymbol() const override;
          bool validMove(Square &new_position, const Board &the_board) override;

          void setFirstMove(bool status) override {
               first_move = status;
          }

          bool getIsFirstMove() {
               return first_move;
          }

          vector<Square> getPossibleMoves(const Board &the_board);
};

#endif
