#include "../include/player.h"
#include <cstdlib>
#include <ctime>


Player::Player(const string& name, const string& colour)
    : name(name), colour(colour) {
    if (name == "human") {
        type = PlayerType::HUMAN;
        cout << "human init." << endl;
    } else if (name == "computer1") {
        type = PlayerType::COMPUTER1;
        cout << "computer init." << endl;
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

bool Player::makeMove(Game* game, Board& board, bool isWhiteTurn) {
    switch (type) {
        case PlayerType::HUMAN:
            return humanMove(game, board, isWhiteTurn);
        case PlayerType::COMPUTER1: {
            cout << "In switch case" << endl;
            return computer1Move(game, board, isWhiteTurn);
        }
        // case PlayerType::COMPUTER2: {
        //     Move computerMove = computer2Move(board);
        //     return board.movePiece(computerMove);
        // }
        // case PlayerType::COMPUTER3: {
        //     Move computerMove = computer3Move(board);
        //     return board.movePiece(computerMove);
        // }
        // case PlayerType::COMPUTER4: {
        //     Move computerMove = computer4Move(board);
        //     return board.movePiece(computerMove);
        // }
        default:
            return false;
    }
}

bool Player::humanMove(Game* game, Board& board, bool isWhiteTurn) {
    string from, to, promotionPiece;
    cin >> from >> to;

    // Check for correct length of input
    if (from.length() != 2 && to.length() != 2) {
        cout << "Invalid coordinate given, try again" << endl;
        return false;
    }  

    if (!('a' <= from[0] && from[0] <= 'h' && 
            '1' <= from[1] && from[1] <= '8' && 
            'a' <= to[0] && to[0] <= 'h' && 
            '1' <= to[1] && to[1] <= '8')) {
        cout << "Invalid coordinate given, try again" << endl;
        return false;
    }


    auto f = new Square(from, game->getBoard());
    auto t = new Square(to, game->getBoard());

    if (!f->getPiece()) {
        cout << "No piece in square, try again" << endl;
        return false;
    }


    if ((!islower(f->getPiece()->getSymbol()) && !isWhiteTurn) || (islower(f->getPiece()->getSymbol()) && isWhiteTurn)) {
        cout << "It's not your turn rn" << endl;
        return false;
    }

    cout << "You chose to move " << f->getPiece()->getSymbol() << endl;

    Move m(f, t, f->getPiece(), game->getBoard());
    if (game->makeMove(m)) {
        isWhiteTurn = !isWhiteTurn;
        bool king_in_check = game->getBoard().isCheck(isWhiteTurn);
        bool king_in_checkmate;

        if (king_in_check) {
            king_in_checkmate = game->getBoard().isCheckmate(isWhiteTurn);
            if (isWhiteTurn) {
                cout << "The white king is in check!" << endl;

                if (king_in_checkmate) cout << "The white king is in checkmate" << endl;
            } else {
                cout << "The black king is in check!" << endl;

                if (king_in_checkmate) cout << "The black king is in checkmate" << endl;
            }
        }

        // TESTING
        game->getBoardModifiable()->pawnGettingPromoted(!isWhiteTurn);
        return true;
    }
    return false;
}


// HELLO ANDY JUNG
bool Player::computer1Move(Game* game, Board& board, bool isWhiteTurn) {
    vector<Move> possible_moves = board.getPossibleMoves(isWhiteTurn);

    cout << "FOUND POSSIBLE MOVES" << endl;


    if (possible_moves.empty()) {
        cout << "No way it's empty" << endl;
        return false; // No valid moves
    }

    // Possible moves
    // cout << "TOTAL POSSIBLE MOVES: " << possible_moves.size() << endl;
    // for (auto move : possible_moves) {

    //     cout << "(" << move.getStartingCoord()->getCoordinates().first << ", " << move.getStartingCoord()->getCoordinates().second << ")   ->   ";
    //     cout << "(" << move.getDestinationCoord()->getCoordinates().first << ", " << move.getDestinationCoord()->getCoordinates().second << ")" << endl;
    // }

    // Select a random move
    Move move = possible_moves[rand() % possible_moves.size()];
    
    // ERROR POINT
    if (game->makeMove(move)) {
        // After making the move, check for check or checkmate
        bool king_in_check = game->getBoard().isCheck(isWhiteTurn);
        bool king_in_checkmate;

        if (king_in_check) {
            king_in_checkmate = game->getBoard().isCheckmate(isWhiteTurn);
            if (isWhiteTurn) {
                cout << "The white king is in check!" << endl;
                if (king_in_checkmate) cout << "The white king is in checkmate" << endl;
            } else {
                cout << "The black king is in check!" << endl;
                if (king_in_checkmate) cout << "The black king is in checkmate" << endl;
            }
        }
        // Update promotion if needed
        game->getBoardModifiable()->pawnGettingPromoted(!isWhiteTurn);
        return true;
    }
    return false;
}

// Move Player::computer2Move(Board& board) {
//     // Slightly more advanced logic than ComputerPlayer1
//     // Example: prioritize captures over random moves
//     srand(static_cast<unsigned>(time(0)));
//     vector<Move> legalMoves = board.getAllLegalMoves(colour);
//     vector<Move> captureMoves;
//     for (const auto& move : legalMoves) {
//         if (move.isCapture()) {
//             captureMoves.push_back(move);
//         }
//     }
//     if (!captureMoves.empty()) {
//         int randomIndex = rand() % captureMoves.size();
//         return captureMoves[randomIndex];
//     }
//     if (!legalMoves.empty()) {
//         int randomIndex = rand() % legalMoves.size();
//         return legalMoves[randomIndex];
//     }
//     return Move();
// }

// Move Player::computer3Move(Board& board) {
//     // More advanced logic, such as simple heuristic evaluation
//     // Implement the logic here
//     return Move();
// }

// Move Player::computer4Move(Board& board) {
//     // Even more advanced logic, such as minimax algorithm with a certain depth
//     // Implement the logic here
//     return Move();
// }
