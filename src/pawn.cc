#include "../include/pawn.h"
#include "../include/board.h"
#include "game.h"

using namespace std;

Pawn::Pawn(Square* current_position, const string& colour, const char symbol) 
     : Piece(current_position, colour, symbol), first_move{true} {}

void Pawn::move(Square* new_position, const Board& the_board) {
     auto old_coords = current_position->getCoordinates();
     int old_x = old_coords.first;
     int old_y = old_coords.second;
     
     if (abs(current_position->getCoordinates().second - new_position->getCoordinates().second) == 2) {
          moved_two_squares = true;
     }
     // Set the position of the piece to the new position provided
     the_board.getSquare(new_position->getCoordinates().first, new_position->getCoordinates().second).setPiece(nullptr);
     the_board.getSquare(new_position->getCoordinates().first, new_position->getCoordinates().second).setPiece(this);
     
     // Clear the piece from the original position
     the_board.getSquare(current_position->getCoordinates().first, current_position->getCoordinates().second).removePiece();

     // If current move is en passant
     Square* en_passant = isCurrentMoveEnPassant(old_coords, *new_position, the_board);
     if (en_passant != nullptr) {
          the_board.getSquare(en_passant->getCoordinates().first, en_passant->getCoordinates().second).removePiece();
     }    

     // Set current position of the piece to the new position
     current_position = new_position;

     // Update the first move flag
     ++move_counter;
     first_move = false;
}


bool Pawn::validMove(Square& new_position, const Board& the_board) {
     auto old_coords = current_position->getCoordinates();
     auto new_coords = new_position.getCoordinates();
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

          // Check if the target coordinates are withMAX_DEPTH
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
     // Check if there any pawns right beside it

     for (int dir : directions) {
          int target_x = old_x + direction * dir;
          int target_y = old_y + direction;

          int en_passant_y = old_y;

          // Check if the target coordinates are within bounds
          if (inBounds(target_x, target_y)) {

               // Check if the target square is occupied
               if (the_board.getSquare(target_x, en_passant_y).isOccupied()) {
                    // Check if the piece on the target square is an opponent's piece
                    if (islower(the_board.getSquare(target_x, en_passant_y).getPiece()->getSymbol()) != islower(symbol)) {
                         // Last move logic
                         stack<Move> move_history = the_board.getMoveHistory();

                         const Move last_move = move_history.top();

                         Square* last_from = last_move.getStartingCoord();
                         Square* last_to = last_move.getDestinationCoord();
                         Piece* last_piece = last_move.getPiece();
                         // Verify that last piece moved was a pawn
                         if (last_piece->getSymbol() == 'P' || last_piece->getSymbol() == 'p') {
                              Pawn* last_piece_pawn = dynamic_cast<Pawn*>(last_piece);

                              if (last_piece_pawn != nullptr) cout << "IS PAWN" << endl; 

                              // Check if last move was a first move and moving two squares
                              if (last_piece_pawn->move_counter == 1 && last_piece_pawn->moved_two_squares) {
                                   possible_moves.emplace_back(Square(target_x, target_y));
                              }
                         }

                    }
               }
          }   
     }

     // Check if new position is in possible moves
     for (Square move : possible_moves) if (move == new_position) return true;
          
     return false;
}


Square* Pawn::isCurrentMoveEnPassant(pair<int, int> old_position, Square& new_position, const Board& the_board) {
     int old_x = old_position.first;
     int old_y = old_position.second;
     int new_x = new_position.getCoordinates().first;
     int new_y = new_position.getCoordinates().second;
     int direction = (islower(getSymbol()) ? -1 : 1);

     if (abs(new_x - old_x) != 1) {
          return nullptr;
     }

     if (abs(new_y - old_y) != 1) {
          return nullptr;
     }
     
     
     int directions[2] = {1, -1};



     for (int dir : directions) {
          int target_x = old_x + direction * dir;
          int target_y = old_y + direction;

          int en_passant_y = old_y;

          // Check if the target coordinates are withMAX_DEPTH
          if (inBounds(target_x, target_y)) {

               // Check if the target square is occupied
               if (the_board.getSquare(target_x, en_passant_y).isOccupied()) {

                    // Check if the piece on the target square is an opponent's piece
                    if (islower(the_board.getSquare(target_x, en_passant_y).getPiece()->getSymbol()) != islower(symbol)) {

                         // Last move logic
                         stack<Move> move_history = the_board.getMoveHistory();

                         const Move last_move = move_history.top();

                         // if (last_move) {

                         Square* last_from = last_move.getStartingCoord();
                         Square* last_to = last_move.getDestinationCoord();
                         Piece* last_piece = last_move.getPiece();

                         // Verify that last piece moved was a pawn
                         if (last_piece->getSymbol() == 'P' || last_piece->getSymbol() == 'p') {
                              Pawn* last_piece_pawn = dynamic_cast<Pawn*>(last_piece);

                              if (last_piece_pawn != nullptr) cout << "IS PAWN" << endl; 


                              // Check if last move was a first move and moving two squares
                              if (last_piece_pawn->move_counter == 1 && last_piece_pawn->moved_two_squares) {
                                   return last_to;
                              }
                         }
                         //}
                    }
               }
          }   
     }
     return nullptr;
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

          // Check if the target coordinates are withMAX_DEPTH
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

     return possible_moves;
}


