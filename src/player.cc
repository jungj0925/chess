#include "../include/player.h"
#include <cstdlib>
#include <ctime>


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
    switch (type) {
        case PlayerType::HUMAN:
            return humanMove(move, board);
        case PlayerType::COMPUTER1: {
            Move computerMove = computer1Move(board);
            return board.movePiece(computerMove);
        }
        case PlayerType::COMPUTER2: {
            Move computerMove = computer2Move(board);
            return board.movePiece(computerMove);
        }
        case PlayerType::COMPUTER3: {
            Move computerMove = computer3Move(board);
            return board.movePiece(computerMove);
        }
        case PlayerType::COMPUTER4: {
            Move computerMove = computer4Move(board);
            return board.movePiece(computerMove);
        }
        default:
            return false;
    }
}

bool Player::humanMove(Move& move, Board& board) {
    Square* fromSquare = move.getStartingCoord();
    Square* toSquare = move.getDestinationCoord();

    if (!fromSquare->isOccupied()) {
        return false; // No piece to move
    }

    Piece* piece = fromSquare->getPiece();
    if (piece->getColor() != colour) {
        return false; // Not the player's piece
    }

    auto possible_moves = piece->possibleMoves(board);
    for (const Move& possible_move : possible_moves) {
        if (possible_move.equals(move)) {
            return board.movePiece(move);
        }
    }

    return false; // Move is not valid
}

Move Player::computer1Move(Board& board) {
    // Simple random move logic
    srand(static_cast<unsigned>(time(0)));
    vector<Move> legalMoves = board.getAllLegalMoves(colour);
    if (!legalMoves.empty()) {
        int randomIndex = rand() % legalMoves.size();
        return legalMoves[randomIndex];
    }
    // Return a dummy move if no legal moves available
    return Move();
}

Move Player::computer2Move(Board& board) {
    // Slightly more advanced logic than ComputerPlayer1
    // Example: prioritize captures over random moves
    srand(static_cast<unsigned>(time(0)));
    vector<Move> legalMoves = board.getAllLegalMoves(colour);
    vector<Move> captureMoves;
    for (const auto& move : legalMoves) {
        if (move.isCapture()) {
            captureMoves.push_back(move);
        }
    }
    if (!captureMoves.empty()) {
        int randomIndex = rand() % captureMoves.size();
        return captureMoves[randomIndex];
    }
    if (!legalMoves.empty()) {
        int randomIndex = rand() % legalMoves.size();
        return legalMoves[randomIndex];
    }
    return Move();
}

Move Player::computer3Move(Board& board) {
    // More advanced logic, such as simple heuristic evaluation
    // Implement the logic here
    return Move();
}

Move Player::computer4Move(Board& board) {
    // Even more advanced logic, such as minimax algorithm with a certain depth
    // Implement the logic here
    return Move();
}
