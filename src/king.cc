#include "king.h"
#include "board.h"

using namespace std;

King::King(Square *current_position, const string& colour, const char symbol)
     : Piece(current_position, colour, symbol), first_move{true} {}

void King::move(Square* new_position, const Board& the_board) {
     // first_move = false;
     auto old_coords = current_position->getCoordinates();
     int old_x = old_coords.first;
     int old_y = old_coords.second;

     // auto queenside_castling_possible = isCastlingPossible(the_board).first;
     // auto kingside_castling_possible = isCastlingPossible(the_board).second;

     // If current move is castling
     auto castling = isCurrentMoveCastling(old_coords, *new_position, the_board);
     // cout << "TESTING" << endl;
     if (castling.first) {
          // cout << "ATTEMPT TO QUEENSIDE" << endl;
          Rook* rook = dynamic_cast<Rook*>(the_board.getSquare(old_x - 4, old_y).getPiece());
          if (rook) {
               rook->move(&the_board.getSquare(old_x - 1, old_y), the_board);
          }
     } else if (castling.second) {
          // cout << "ATTEMPT TO KINGSIDE" << endl;
          Rook* rook = dynamic_cast<Rook*>(the_board.getSquare(old_x + 3, old_y).getPiece());
          if (rook) {
               rook->move(&the_board.getSquare(old_x + 1, old_y), the_board);
          }
     }


     // Set the position of the piece to the new position provided
     the_board.getSquare(new_position->getCoordinates().first, new_position->getCoordinates().second).setPiece(this);
     the_board.getSquare(old_x, old_y).setPiece(nullptr);
     current_position = new_position;

     // Set first move to false afetr making the move
     first_move = false;
}


bool King::validMove(Square& new_position, const Board& the_board) {
     auto old_coords = current_position->getCoordinates();

     int old_x = old_coords.first;
     int old_y = old_coords.second;

     vector<pair<int, int>> all_moves = {
          {old_x - 1, old_y + 1},
          {old_x, old_y + 1},
          {old_x + 1, old_y + 1},
          {old_x - 1, old_y},
          {old_x + 1, old_y},
          {old_x - 1, old_y - 1},
          {old_x, old_y - 1},
          {old_x + 1, old_y - 1}
     };

     vector<Square> possible_moves;

     // Check if the new coords are in bounds and valid

     // Add logic for the king to not be able to move to squares that would also put it in check
     for (auto move : all_moves) {
          if (inBounds(move.first, move.second)) {
               Square& temp_square = the_board.getSquare(move.first, move.second);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    // break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }

     // Castling
     // To be finished
     if (isCastlingPossible(the_board).first) {
          Square& temp_square = the_board.getSquare(old_x - 2, old_y);
          possible_moves.push_back(temp_square);
     } else if (isCastlingPossible(the_board).second) {
          Square& temp_square = the_board.getSquare(old_x + 2, old_y);
          possible_moves.push_back(temp_square);
     }

     // Check if new position is in possible moves
     for (Square move : possible_moves) if (move == new_position) return true;

     return false;
}

vector<Square> King::getPossibleMoves(const Board& the_board) {
     auto old_coords = current_position->getCoordinates();

     int old_x = old_coords.first;
     int old_y = old_coords.second;

     vector<pair<int, int>> all_moves = {
         {old_x - 1, old_y + 1},
         {old_x, old_y + 1},
         {old_x + 1, old_y + 1},
         {old_x - 1, old_y},
         {old_x + 1, old_y},
         {old_x - 1, old_y - 1},
         {old_x, old_y - 1},
         {old_x + 1, old_y - 1}
     };

     vector<Square> possible_moves;

     // Check if the new coords are in bounds and valid

     // Add logic for the king to not be able to move to squares that would also put it in check
     for (auto move : all_moves) {
          if (inBounds(move.first, move.second)) {
               Square& temp_square = the_board.getSquare(move.first, move.second);
               if (temp_square.isOccupied()) {
                    if (islower(temp_square.getPiece()->getSymbol()) != islower(getSymbol())) {
                         possible_moves.push_back(temp_square); // Add only if it's an opponent's piece
                    }
                    // break; // Stop after encountering any piece
               }
               possible_moves.push_back(temp_square);
          }
     }

     // Castling
     // To be finished
     if (isCastlingPossible(the_board).first) {
          Square& temp_square = the_board.getSquare(old_x - 2, old_y);
          possible_moves.push_back(temp_square);
     } else if (isCastlingPossible(the_board).second) {
          Square& temp_square = the_board.getSquare(old_x + 2, old_y);
          possible_moves.push_back(temp_square);
     }

     return possible_moves;
}


char King::getSymbol() const {
     return symbol;
}


// first: queenside
// second: kingside
pair<bool, bool> King::isCastlingPossible(const Board& the_board) {
     auto old_coords = current_position->getCoordinates();
     int old_x = old_coords.first;
     int old_y = old_coords.second;

     bool queenside = false;
     bool kingside = false;

     if (first_move) {
          // Queenside
          if ( inBounds(old_x - 1, old_y) &&
               inBounds(old_x - 2, old_y) &&
               inBounds(old_x - 3, old_y)) {
               
               if (!the_board.getSquare(old_x - 1, old_y).isOccupied() &&
                   !the_board.getSquare(old_x - 2, old_y).isOccupied() &&
                   !the_board.getSquare(old_x - 3, old_y).isOccupied())
               {
                    Rook *rook = dynamic_cast<Rook *>(the_board.getSquare(old_x - 4, old_y).getPiece());
                    if (rook) {
                         if (rook->getIsFirstMove())
                              queenside = true;
                    }
               }
          }

          // Kingside 
          if ( inBounds(old_x + 1, old_y) &&
               inBounds(old_x + 2, old_y)) {

               if ( !the_board.getSquare(old_x + 1, old_y).isOccupied() && 
                    !the_board.getSquare(old_x + 2, old_y).isOccupied()) {
                    Rook* rook = dynamic_cast<Rook*>(the_board.getSquare(old_x + 3, old_y).getPiece());
                    if (rook) {
                         //cout << "A ROOK EXISTS" << endl;
                         if (rook->getIsFirstMove()) {
                              kingside = true;
                              //cout << "ROOK believes Kingside is possible: " << kingside << endl;
                         }
                    }
               }
          }


     }

     return make_pair(queenside, kingside);
}


pair<bool, bool> King::isCurrentMoveCastling(pair<int, int> old_position, Square& new_position, const Board &the_board) {
     auto new_coords = new_position.getCoordinates();

     int old_x = old_position.first;
     int new_x = new_coords.first;

     bool queenside_possible = isCastlingPossible(the_board).first;
     bool kingside_possible = isCastlingPossible(the_board).second;

     bool current_move_queenside = (new_x - old_x == -2);
     bool current_move_kingside = (new_x - old_x == 2);

     return make_pair(queenside_possible && current_move_queenside, kingside_possible && current_move_kingside);
}
