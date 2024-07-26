#include "knight.h"
#include "board.h"

using namespace std;

Knight::Knight(Square *current_position, const string &colour, const char symbol)
     : Piece(current_position, colour, symbol) {}

void Knight::move(Square* new_position, const Board& the_board) {
     // Set the position of the piece to the new position provided
     the_board.getSquare(new_position->getCoordinates().first, new_position->getCoordinates().second).setPiece(this);
     
     // Clear the piece from the original position
     the_board.getSquare(current_position->getCoordinates().first, current_position->getCoordinates().second).setPiece(nullptr);

     // Set current position of the piece to the new position
     current_position = new_position;
}


bool Knight::validMove(Square& new_position, const Board& the_board) {
    auto old_coords = current_position->getCoordinates();
    auto new_coords = new_position.getCoordinates();

    int old_x = old_coords.first;
    int old_y = old_coords.second;

    vector<pair<int, int>> possible_moves = {
        {old_x - 1, old_y + 2},
        {old_x + 1, old_y + 2},
        {old_x - 2, old_y + 1},
        {old_x + 2, old_y + 1},
        {old_x - 2, old_y - 1},
        {old_x + 2, old_y - 1},
        {old_x - 1, old_y - 2},
        {old_x + 1, old_y - 2}
    };

    // Check if the new coords are in bounds and valid
    for (const auto& move : possible_moves) {
        if (inBounds(move.first, move.second)) {
            Square& possible_square = the_board.getSquare(move.first, move.second);
            if (possible_square.getCoordinates() == new_coords) {
                // Check if the square is occupied by the same color
                if (possible_square.isOccupied() && islower(possible_square.getPiece()->getSymbol()) == islower(symbol)) {
                    return false;
                }
                return true;
            }
        }
    }

    return false;
}

char Knight::getSymbol() const {
     return symbol;
}

std::vector<Square> Knight::getPossibleMoves(const Board &the_board) {
    auto old_coords = current_position->getCoordinates();
    int old_x = old_coords.first;
    int old_y = old_coords.second;

    std::vector<Square> final_possible_moves;
    std::vector<std::pair<int, int>> possible_moves = {
        {old_x - 1, old_y + 2},
        {old_x + 1, old_y + 2},
        {old_x - 2, old_y + 1},
        {old_x + 2, old_y + 1},
        {old_x - 2, old_y - 1},
        {old_x + 2, old_y - 1},
        {old_x - 1, old_y - 2},
        {old_x + 1, old_y - 2}
    };

    // Check if the new coords are in bounds and valid
    for (const auto& move : possible_moves) {
        if (inBounds(move.first, move.second)) {
            Square& possible_square = the_board.getSquare(move.first, move.second);
            
            if (!possible_square.isOccupied() || islower(possible_square.getPiece()->getSymbol()) != islower(symbol)) {
                final_possible_moves.emplace_back(possible_square);
            }
        }
    }

    return final_possible_moves;
}
