#include "../include/pawn.h"
#include "../include/board.h"
#include "game.h"

using namespace std;

Pawn::Pawn(Square* current_position, const string& colour, const char symbol) 
     : Piece(current_position, colour, symbol), first_move{true} {}

// void Pawn::move(Square* new_position, const Board& the_board) {
//           // Check for validity
//      // if (!validMove(*new_position, the_board)) {
//      //      cout << "This is not a valid move" << endl;
//      //      return;
//      // }

//      // // Capturing Pieces
//      // if (new_position->getPiece() != nullptr && 
//      //      islower(new_position->getPiece()->getSymbol()) != islower(symbol)) {
//      //      new_position->removePiece(); // Remove the piece being captured
//      // }

//      // Set the position of the piece to the new position provided
//      the_board.getSquare(new_position->getCoordinates().first, new_position->getCoordinates().second).setPiece(this);
     
//      // Clear the piece from the original position
//      the_board.getSquare(current_position->getCoordinates().first, current_position->getCoordinates().second).removePiece();

//      // Set current position of the piece to the new position
//      current_position = new_position;

//      // Update the first move flag
//      first_move = false;
// }

void Pawn::move(Square* new_position, const Board& the_board) {
     auto old_coords = current_position->getCoordinates();
     int old_x = old_coords.first;
     int old_y = old_coords.second;

     // cout << "CUR_Y : " << current_position->getCoordinates().second << "  NEW_Y: " << new_position->getCoordinates().second << endl;
     
     if (abs(current_position->getCoordinates().second - new_position->getCoordinates().second) == 2) {
          moved_two_squares = true;
     }

     // cout << "2 SQUARES: " << moved_two_squares << endl;

     // Set the position of the piece to the new position provided
     the_board.getSquare(new_position->getCoordinates().first, new_position->getCoordinates().second).setPiece(this);
     
     // Clear the piece from the original position
     the_board.getSquare(current_position->getCoordinates().first, current_position->getCoordinates().second).removePiece();

     // If current move is en passant
     Square* en_passant = isCurrentMoveEnPassant(old_coords, *new_position, the_board);
     if (en_passant != nullptr) {
          // cout << "DELETING PIECE" << endl;

          // cout << en_passant->getCoordinates().first

          // Temporary
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
     
     // Check if there any pawns right beside it

     for (int dir : directions) {
          int target_x = old_x + direction * dir;
          int target_y = old_y + direction;

          int en_passant_y = old_y;

          // Check if the target coordinates are within bounds
          if (inBounds(target_x, target_y)) {

               cout << "IN BOUNDS" << endl;
               // Check if the target square is occupied
               if (the_board.getSquare(target_x, en_passant_y).isOccupied()) {

                    cout << "IS OCCUPIED" << endl;
                    // Check if the piece on the target square is an opponent's piece
                    if (islower(the_board.getSquare(target_x, en_passant_y).getPiece()->getSymbol()) != islower(symbol)) {

                         cout << "IS OPPONENT" << endl;
                         // Last move logic
                         stack<Move> move_history = the_board.getMoveHistory();

                         // // move_history.pop();
                         // move_history.pop();
                         // auto x = move_history.top();
                         // Square* f = x->getStartingCoord();
                         // Square* t = x->getDestinationCoord();

                         // cout << "GOT X FROM SQUARE: " << "[" << f->getCoordinates().first << ", " << f->getCoordinates().second << "]" << endl;
                         // cout << "GOT X TO SQUARE: " << "[" << t->getCoordinates().first << ", " << t->getCoordinates().second << "]" << endl;

                         const Move last_move = move_history.top();

                         // if (last_move) {

                              Square* last_from = last_move.getStartingCoord();
                              Square* last_to = last_move.getDestinationCoord();
                              Piece* last_piece = last_move.getPiece();

                              cout << "GOT LAST FROM SQUAE: " << "[" << last_from->getCoordinates().first << ", " << last_from->getCoordinates().second << "]" << endl;
                              cout << "GOT LAST TO SQUARE: " << "[" << last_to->getCoordinates().first << ", " << last_to->getCoordinates().second << "]" << endl;

                              // Verify that last piece moved was a pawn
                              if (last_piece->getSymbol() == 'P' || last_piece->getSymbol() == 'p') {
                                   Pawn* last_piece_pawn = dynamic_cast<Pawn*>(last_piece);

                                   if (last_piece_pawn != nullptr) cout << "IS PAWN" << endl; 

                                   cout << "MOVE COUNTER: " << last_piece_pawn->move_counter << endl;
                                   cout << "MOVED TWO SQUARES: " << last_piece_pawn->moved_two_squares << endl;

                                   // Check if last move was a first move and moving two squares
                                   if (last_piece_pawn->move_counter == 1 && last_piece_pawn->moved_two_squares) {

                                        cout << "LAST MOVE WAS A FIRST WHILE MOVING 2 SQUARES" << endl;
                                        possible_moves.emplace_back(Square(target_x, target_y));
                                   }
                              }
                         //}
                    }
               }
          }   
     }




     // auto last_pawn_move = the_board.getMoveHistory().top().getDestinationCoord();
     // stack<Move> move_history = the_board.getMoveHistory();
     // if (!move_history.empty()) {
     //      Move last_move = move_history.top();
     //      Square* last_from = last_move.getStartingCoord();
     //      Square* last_to = last_move.getDestinationCoord();
     //      Piece* last_piece = last_move.getPiece();

     //      // Check if last move was a pawn move
     //      if (last_piece != nullptr && (last_piece->getSymbol() == 'P' || last_piece->getSymbol() == 'p')) {
     //           Pawn* last_piece_pawn = dynamic_cast<Pawn*>(last_piece);

     //           // Check if last move was a first move and moving two squares
     //           if (last_piece_pawn->move_counter == 1 && last_piece_pawn->moved_two_squares) {
     //                // Capturing
     //                int directions[2] = {1, -1};

     //                for (int dir : directions) {
     //                     int target_x = old_x + direction * dir;
     //                     int target_y = old_y + direction;

     //                     // Check if the target coordinates are within bounds
     //                     if (target_x >= 0 && target_x < 8 && target_y >= 0 && target_y < 8) {
     //                          // Check if the target square is occupied
     //                          if (the_board.getSquare(target_x, target_y).isOccupied()) {
     //                               // Check if the piece on the target square is an opponent's piece
     //                               if (islower(the_board.getSquare(target_x, target_y).getPiece()->getSymbol()) != islower(symbol)) {
     //                                    possible_moves.emplace_back(Square(target_x, target_y));
     //                               }
     //                          }
     //                     }   
     //                }

     //           }
     //      }
     // }


     // Check if new position is in possible moves
     for (Square move : possible_moves) if (move == new_position) return true;

     for (auto move : possible_moves) {
          cout << move.getCoordinates().first << ", " << move.getCoordinates().second << endl;
     }
          
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

          // Check if the target coordinates are within bounds
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

     return possible_moves;
}


