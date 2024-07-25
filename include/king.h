#ifndef KING_H
#define KING_H
#include "piece.h"

class King : public Piece { 
     protected:
          bool first_move;

     public:
          King(Square *current_position, const string& colour,  const char symbol);
          ~King() override{};
          void move(Square *new_position, const Board &the_board) override;
          char getSymbol() const override;
          bool validMove(Square &new_position, const Board &the_board) override;

          pair<bool, bool> isCastlingPossible(const Board& the_board);
          pair<bool, bool> isCurrentMoveCastling(pair<int, int> old_position, Square& new_position, const Board &the_board);

          void setFirstMove(bool status) override {
               first_move = status;
          }

          vector<Square> getPossibleMoves(const Board &the_board);
};

#endif