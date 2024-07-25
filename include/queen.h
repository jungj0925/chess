#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Board;

class Queen : public Piece { 
     public:
          Queen(Square *current_position, const string &colour, const char symbol);
          ~Queen() override{};
          void move(Square *new_position, const Board &the_board) override;
          char getSymbol() const override;
          bool validMove(Square &new_position, const Board &the_board) override;
};

#endif
