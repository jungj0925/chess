#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include "square.h"
// #include "board.h"

class Board;
// class Square;

using namespace std;

class Piece {     
     protected:
          Square* current_position;
          const string& colour;
          const char symbol;

     public:
          Piece(Square *current_position, const string& colour,  const char symbol);
          virtual ~Piece();

          const string& getColour() const;
          virtual char getSymbol() const = 0;

          bool inBounds(int x, int y);

          virtual void move(Square *new_position, const Board &the_board) = 0;
          virtual bool validMove(Square &new_position, const Board &the_board) = 0;
          virtual void setFirstMove(bool status) {}


          Square* getCurrentPosition() {
               if (current_position == nullptr) cout << "CURRENT POS IS NULL" << endl;
               return current_position;
          }
};

#endif
