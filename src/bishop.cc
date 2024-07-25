#include "bishop.h"
#include "square.h"
#include "board.h"

using namespace std;

Bishop::Bishop(Square *current_position, const string& colour, const char symbol)
     : Piece(current_position, colour, symbol) {}

void Bishop::move(Square* new_position, const Board& the_board) {
          // Check for validity
     // if (!validMove(*new_position, the_board)) {
     //      cout << "This is not a valid move" << endl;
     //      return;
     // }

     // Capturing Pieces
     // if (new_position->getPiece() != nullptr && 
     //      islower(new_position->getPiece()->getSymbol()) != islower(symbol)) {
     //      new_position->removePiece(); // Remove the piece being captured
     // }

     // Set the position of the piece to the new position provided
     the_board.getSquare(new_position->getCoordinates().first, new_position->getCoordinates().second).setPiece(this);
     
     // Clear the piece from the original position
     the_board.getSquare(current_position->getCoordinates().first, current_position->getCoordinates().second).setPiece(nullptr);

     // Set current position of the piece to the new position
     current_position = new_position;

}


bool Bishop::validMove(Square& new_position, const Board& the_board) {
     auto old_coords = current_position->getCoordinates();
     // auto new_coords = new_position.getCoordinates();

     int old_x = old_coords.first;
     int old_y = old_coords.second;

     vector<Square> possible_moves;

     // Add up-left moves
     for (int temp_x = old_x - 1, temp_y = old_y + 1; temp_x >= 0 && temp_y <= 7; --temp_x, ++temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.emplace_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.emplace_back(temp_square);
          }
     }

     // Add up-right moves
     for (int temp_x = old_x + 1, temp_y = old_y + 1; temp_x <= 7 && temp_y <= 7; ++temp_x, ++temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.emplace_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.emplace_back(temp_square);
          }
     }

     // Add down-left moves
     for (int temp_x = old_x - 1, temp_y = old_y - 1; temp_x >= 0 && temp_y >= 0; --temp_x, --temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.emplace_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.emplace_back(temp_square);
          }
     }

     // Add down-right moves
     for (int temp_x = old_x + 1, temp_y = old_y - 1; temp_x <= 7 && temp_y >= 0; ++temp_x, --temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.emplace_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.emplace_back(temp_square);
          }
     }
     // Check if new position is in possible moves
     for (Square& move : possible_moves) if (move == new_position) return true;
          
     return false;
}

char Bishop::getSymbol() const {
     return symbol;
}

vector<Square> Bishop::getPossibleMoves(const Board &the_board) {
     auto old_coords = current_position->getCoordinates();
     // auto new_coords = new_position.getCoordinates();

     int old_x = old_coords.first;
     int old_y = old_coords.second;

     vector<Square> possible_moves;

     // Add up-left moves
     for (int temp_x = old_x - 1, temp_y = old_y + 1; temp_x >= 0 && temp_y <= 7; --temp_x, ++temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.emplace_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.emplace_back(temp_square);
          }
     }

     // Add up-right moves
     for (int temp_x = old_x + 1, temp_y = old_y + 1; temp_x <= 7 && temp_y <= 7; ++temp_x, ++temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.emplace_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.emplace_back(temp_square);
          }
     }

     // Add down-left moves
     for (int temp_x = old_x - 1, temp_y = old_y - 1; temp_x >= 0 && temp_y >= 0; --temp_x, --temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.emplace_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.emplace_back(temp_square);
          }
     }

     // Add down-right moves
     for (int temp_x = old_x + 1, temp_y = old_y - 1; temp_x <= 7 && temp_y >= 0; ++temp_x, --temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.emplace_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.emplace_back(temp_square);
          }
     }
     return possible_moves;
}
