#include "../include/square.h"
#include "../include/board.h"

using namespace std;

Square::Square(int col, int row, Piece* the_piece) 
     : col{col}, row{row}, the_piece{the_piece} {}

Square::Square(int col, int row)
    : col{col}, row{row}, the_piece{nullptr} {}

Square::Square(const string& position, const Board& board) {
     char file = position[0]; // 'a' to 'h'
     char rank = position[1]; // '1' to '8'
    
     col = file - 'a'; // Convert '1'-'8' to 0-7
     row = rank - '1'; // Convert 'a'-'h' to 0-7

     cout << col << " " << row << endl;

     the_piece = board.getSquare(col, row).getPiece();
}

Square::~Square() { 
     // if (the_piece != nullptr) delete the_piece; 
};

bool Square::isOccupied() {
     if (the_piece != nullptr) return true;
     return false;
}

Piece* Square::getPiece() {
     return the_piece;
}

void Square::setPiece(Piece* new_piece) {
     the_piece = new_piece;
}

void Square::removePiece() {
     the_piece = nullptr;
}

pair<int, int> Square::getCoordinates() const {
     return make_pair(col, row);
}

bool Square::operator==(const Square& rhs) const {
    return (col == rhs.col) && (row == rhs.row);
}
