#include "../include/move.h"
// 110

// // Helper function to convert coordinate string to Square*
// Square Move::coordinateToSquare(const string& coord) {

//     if (coord.length() != 2) return nullptr; // Invalid coordinate length
    
//     char file = coord[0]; // 'a' to 'h'
//     char rank = coord[1]; // '1' to '8'
    
//     int x = rank - '1'; // Convert '1'-'8' to 0-7
//     int y = file - 'a'; // Convert 'a'-'h' to 0-7
    
//     if (x < 0 || x >= 8 || y < 0 || y >= 8) return nullptr; // Out of bounds
    
//     // Assuming Board is a singleton or you have a method to get a specific Square
//     return board->getSquare(x, y); // Implement this method in Board
// }

// // Constructor that takes coordinate strings
// Move::Move(const string& fromStr, const string& toStr, Piece* piece, Board* board)
//     : piece(piece), board(board) {
//     from = coordinateToSquare(fromStr);
//     to = coordinateToSquare(toStr);
// }

// Constructor that takes Square pointers

// Destructor
