#include "pawn.h"
#include "board.h"

using namespace std;

Pawn::Pawn(Square* current_position, const string& colour, const char symbol) 
     : Piece(current_position, colour, symbol), first_move{true} {}

void Pawn::move(Square* new_position, const Board& the_board) {
          // Check for validity
     // if (!validMove(*new_position, the_board)) {
     //      cout << "This is not a valid move" << endl;
     //      return;
     // }

     // // Capturing Pieces
     // if (new_position->getPiece() != nullptr && 
     //      islower(new_position->getPiece()->getSymbol()) != islower(symbol)) {
     //      new_position->removePiece(); // Remove the piece being captured
     // }

     // Set the position of the piece to the new position provided
     the_board.getSquare(new_position->getCoordinates().first, new_position->getCoordinates().second).setPiece(this);
     
     // Clear the piece from the original position
     the_board.getSquare(current_position->getCoordinates().first, current_position->getCoordinates().second).removePiece();

     // Set current position of the piece to the new position
     current_position = new_position;

     // Update the first move flag
     first_move = false;
}


bool Pawn::validMove(Square& new_position, const Board& the_board) {
     auto old_coords = current_position->getCoordinates();
     auto new_coords = new_position.getCoordinates();
     int direction = (islower(getSymbol()) ? -1 : 1);

     int old_x = old_coords.first;
     int old_y = old_coords.second;

     vector<Square> possible_moves;

     // Checking for 2 spaces forward on first move
     // bool possible = first_move;
     // for (int i = 1; i <= 2; ++i) {
     //      if (the_board.getSquare(old_x, old_y + i * direction).isOccupied()) {
     //           possible = false;
     //           break;
     //      }
     // }

     // if (possible) {
     //      possible_moves.emplace_back(Square(old_x, old_y + 2 * direction));
     //      possible_moves.emplace_back(Square(old_x, old_y + 1 * direction));
     // } else {

     // }


     // // 1 square forward
     // if (!the_board.getSquare(old_x, old_y + direction).isOccupied())
     //      possible_moves.emplace_back(Square(old_x, old_y + direction));

     //cout << "Everything is going well" << endl;

     if (inBounds(old_x, old_y + 1 * direction)) {
          if (!the_board.getSquare(old_x, old_y + 1 * direction).isOccupied()) {
               possible_moves.emplace_back(Square(old_x, old_y + direction));
               if (inBounds(old_x, old_y + 2 * direction)) {
                    if (first_move && !the_board.getSquare(old_x, old_y + 2 * direction).isOccupied()) {
                         possible_moves.emplace_back(Square(old_x, old_y + 2 * direction));
                    }
               }

          }
     }


     // Capturing
     int directions[2] = {1, -1};

     for (int dir : directions) {
          int target_x = old_x + direction * dir;
          int target_y = old_y + direction;

          // Check if the target coordinates are within bounds
          if (target_x >= 0 && target_x < 8 && target_y >= 0 && target_y < 8) {
               // Check if the target square is occupied
               if (the_board.getSquare(target_x, target_y).isOccupied()) {
                    // Check if the piece on the target square is an opponent's piece
                    if (islower(the_board.getSquare(target_x, target_y).getPiece()->getSymbol()) != islower(symbol)) {
                         possible_moves.emplace_back(Square(target_x, target_y));
                    }
               }
          }   
     }

     // En passant
     // To be finished

     // Check if new position is in possible moves
     for (Square move : possible_moves) if (move == new_position) return true;
          
     return false;
}

char Pawn::getSymbol() const {
     return symbol;
}

std::vector<Square> Pawn::getPossibleMoves(const Board &the_board) {
     auto old_coords = current_position->getCoordinates();
     int direction = (islower(getSymbol()) ? -1 : 1);

     int old_x = old_coords.first;
     int old_y = old_coords.second;

     vector<Square> possible_moves;

     if (inBounds(old_x, old_y + 1 * direction)) {
          if (!the_board.getSquare(old_x, old_y + 1 * direction).isOccupied()) {
               possible_moves.emplace_back(Square(old_x, old_y + direction));
               if (inBounds(old_x, old_y + 2 * direction)) {
                    if (first_move && !the_board.getSquare(old_x, old_y + 2 * direction).isOccupied()) {
                         possible_moves.emplace_back(Square(old_x, old_y + 2 * direction));
                    }
               }

          }
     }


     // Capturing
     int directions[2] = {1, -1};

     for (int dir : directions) {
          int target_x = old_x + direction * dir;
          int target_y = old_y + direction;

          // Check if the target coordinates are within bounds
          if (target_x >= 0 && target_x < 8 && target_y >= 0 && target_y < 8) {
               // Check if the target square is occupied
               if (the_board.getSquare(target_x, target_y).isOccupied()) {
                    // Check if the piece on the target square is an opponent's piece
                    if (islower(the_board.getSquare(target_x, target_y).getPiece()->getSymbol()) != islower(symbol)) {
                         possible_moves.emplace_back(Square(target_x, target_y));
                    }
               }
          }   
     }
}
