#include "queen.h"
#include "board.h"

using namespace std;

Queen::Queen(Square *current_position, const string &colour, const char symbol)
    : Piece(current_position, colour, symbol) {}

void Queen::move(Square* new_position, const Board& the_board) {
     // Set the position of the piece to the new position provided
     the_board.getSquare(new_position->getCoordinates().first, new_position->getCoordinates().second).setPiece(this);
     
     // Clear the piece from the original position
     the_board.getSquare(current_position->getCoordinates().first, current_position->getCoordinates().second).setPiece(nullptr);

     // Set current position of the piece to the new position
     current_position = new_position;
}


bool Queen::validMove(Square &new_position, const Board &the_board) {
     auto old_coords = current_position->getCoordinates();
     // auto new_coords = new_position.getCoordinates();

     int old_x = old_coords.first;
     int old_y = old_coords.second;

     vector<Square> possible_moves;

     // Add horizontal moves to the right
    for (int temp_x = old_x + 1; temp_x < 8; ++temp_x) {
        if (inBounds(temp_x, old_y)) {
            Square& temp_square = the_board.getSquare(temp_x, old_y);
            if (temp_square.isOccupied()) {
                if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                    possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                }
                break; // Stop after encountering any piece
            }
            possible_moves.push_back(temp_square);
        }
    }

    // Add horizontal moves to the left
    for (int temp_x = old_x - 1; temp_x >= 0; --temp_x) {
        if (inBounds(temp_x, old_y)) {
            Square& temp_square = the_board.getSquare(temp_x, old_y);
            if (temp_square.isOccupied()) {
                if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                    possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                }
                break; // Stop after encountering any piece
            }
            possible_moves.push_back(temp_square);
        }
    }

    // Add vertical moves upwards
    for (int temp_y = old_y + 1; temp_y < 8; ++temp_y) {
        if (inBounds(old_x, temp_y)) {
            Square& temp_square = the_board.getSquare(old_x, temp_y);
            if (temp_square.isOccupied()) {
               if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                    possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
               }
               break; // Stop after encountering any piece
            }
            possible_moves.push_back(temp_square);
        }
    }

    // Add vertical moves downwards
    for (int temp_y = old_y - 1; temp_y >= 0; --temp_y) {
        if (inBounds(old_x, temp_y)) {
            Square& temp_square = the_board.getSquare(old_x, temp_y);
            if (temp_square.isOccupied()) {
                if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                    possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                }
                break; // Stop after encountering any piece
            }
            possible_moves.push_back(temp_square);
        }
    }

     // Add up-left moves
     for (int temp_x = old_x - 1, temp_y = old_y + 1; temp_x >= 0 && temp_y <= 7; --temp_x, ++temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }

     // Add up-right moves
     for (int temp_x = old_x + 1, temp_y = old_y + 1; temp_x <= 7 && temp_y <= 7; ++temp_x, ++temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }

     // Add down-left moves
     for (int temp_x = old_x - 1, temp_y = old_y - 1; temp_x >= 0 && temp_y >= 0; --temp_x, --temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }

     // Add down-right moves
     for (int temp_x = old_x + 1, temp_y = old_y - 1; temp_x <= 7 && temp_y >= 0; ++temp_x, --temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }
     
     // Check if new position is in possible moves
     for (Square move : possible_moves) if (move == new_position) return true;
          
     return false;
}

char Queen::getSymbol() const {
     return symbol;
}

std::vector<Square> Queen::getPossibleMoves(const Board &the_board) {
     auto old_coords = current_position->getCoordinates();

     int old_x = old_coords.first;
     int old_y = old_coords.second;

     vector<Square> possible_moves;

     // Add horizontal moves to the right
    for (int temp_x = old_x + 1; temp_x < 8; ++temp_x) {
        if (inBounds(temp_x, old_y)) {
            Square& temp_square = the_board.getSquare(temp_x, old_y);
            if (temp_square.isOccupied()) {
                if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                    possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                }
                break; // Stop after encountering any piece
            }
            possible_moves.push_back(temp_square);
        }
    }

    // Add horizontal moves to the left
    for (int temp_x = old_x - 1; temp_x >= 0; --temp_x) {
        if (inBounds(temp_x, old_y)) {
            Square& temp_square = the_board.getSquare(temp_x, old_y);
            if (temp_square.isOccupied()) {
                if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                    possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                }
                break; // Stop after encountering any piece
            }
            possible_moves.push_back(temp_square);
        }
    }

    // Add vertical moves upwards
    for (int temp_y = old_y + 1; temp_y < 8; ++temp_y) {
        if (inBounds(old_x, temp_y)) {
            Square& temp_square = the_board.getSquare(old_x, temp_y);
            if (temp_square.isOccupied()) {
               if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                    possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
               }
               break; // Stop after encountering any piece
            }
            possible_moves.push_back(temp_square);
        }
    }

    // Add vertical moves downwards
    for (int temp_y = old_y - 1; temp_y >= 0; --temp_y) {
        if (inBounds(old_x, temp_y)) {
            Square& temp_square = the_board.getSquare(old_x, temp_y);
            if (temp_square.isOccupied()) {
                if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                    possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                }
                break; // Stop after encountering any piece
            }
            possible_moves.push_back(temp_square);
        }
    }

     // Add up-left moves
     for (int temp_x = old_x - 1, temp_y = old_y + 1; temp_x >= 0 && temp_y <= 7; --temp_x, ++temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }

     // Add up-right moves
     for (int temp_x = old_x + 1, temp_y = old_y + 1; temp_x <= 7 && temp_y <= 7; ++temp_x, ++temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }

     // Add down-left moves
     for (int temp_x = old_x - 1, temp_y = old_y - 1; temp_x >= 0 && temp_y >= 0; --temp_x, --temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }

     // Add down-right moves
     for (int temp_x = old_x + 1, temp_y = old_y - 1; temp_x <= 7 && temp_y >= 0; ++temp_x, --temp_y) {
          if (inBounds(temp_x, temp_y)) {
               Square& temp_square = the_board.getSquare(temp_x, temp_y);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }
     return possible_moves;
}
