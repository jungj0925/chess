#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece { 
     public:
          Bishop(Square *current_position, const string &colour, const char symbol);
          ~Bishop() override{};
          void move(Square *new_position, const Board &the_board) override;
          char getSymbol() const override;
          bool validMove(Square &new_position, const Board &the_board) override;

          vector<Square> getPossibleMoves(const Board &the_board);
};

#endif
