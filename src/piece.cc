#include "piece.h"
#include <iostream>

Piece::Piece(Square *current_position, const string& colour, const char symbol) 
     : current_position{current_position}, colour{colour}, symbol{symbol} {};

Piece::~Piece() {};

const string& Piece::getColour() const { return colour; }

bool Piece::inBounds(int x, int y) {
     return x >= 0 && x < 8 && y >= 0 && y < 8;
}
