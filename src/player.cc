#include "../include/player.h"

Player::Player(const string& name, const string& colour)
    : name(name), colour(colour) {
    if (name == "human") {
        type = PlayerType::HUMAN;
    } else if (name == "computer1") {
        type = PlayerType::COMPUTER1;
    } else if (name == "computer2") {
        type = PlayerType::COMPUTER2;
    } else if (name == "computer3") {
        type = PlayerType::COMPUTER3;
    } else if (name == "computer4") {
        type = PlayerType::COMPUTER4;
    } else {
        throw invalid_argument("Unknown player type");
    }
}

string& Player::getColour() {
    return colour;
}

PlayerType Player::getType() const {
    return type;
}

bool Player::makeMove(Move& move, Board& board) {
//     switch (type) {
//         {
//         case PlayerType::HUMAN:
//             const Square* fromSquare = move.getStartingCoord();
//             const Square* toSquare = move.getDestinationCoord();

//             if (!fromSquare->isOccupied()) {
//                 return false; // No piece to move
//             }

//             Piece* piece = fromSquare->getPiece();
//             if (piece->getColor() != colour) {
//                 return false; // Not the player's piece
//             }
// spiece->possibleMoves(board);
//             for (const Move& possible_move : possible_moves) {
//                 if (possible_move.equals(move)) {
//                     board.movePiece(move);
//                     return true;
//                 }
//             }

//             return false; // Move is not valid
//             break;
//         }
//         case PlayerType::COMPUTER1:
//             // Logic for computer1 move
//             break;
//         case PlayerType::COMPUTER2:
//             // Logic for computer2 move
//             break;
//         case PlayerType::COMPUTER3:
//             // Logic for computer3 move
//             break;
//         case PlayerType::COMPUTER4:
//             // Logic for computer4 move
//             break;
//     }
}

