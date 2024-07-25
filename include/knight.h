#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece { 
     public:
          Knight(Square *current_position, const string& colour, const char symbol);
          ~Knight() override{};
          void move(Square *new_position, const Board &the_board) override;
          char getSymbol() const override;
          bool validMove(Square &new_position, const Board &the_board) override;
};


#endif
