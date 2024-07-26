#include "../include/player.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>


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

bool Player::makeMove(Game* game, Board& board, bool isWhiteTurn) {
    switch (type) {
        case PlayerType::HUMAN:
            return humanMove(game, board, isWhiteTurn);
        case PlayerType::COMPUTER1: {
            return computer1Move(game, board, isWhiteTurn);
        }
        case PlayerType::COMPUTER2: {
            return computer2Move(game, board, isWhiteTurn);
        }
        case PlayerType::COMPUTER3: {
            return computer3Move(game, board, isWhiteTurn);
        }
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

    // cout << "FOUND POSSIBLE MOVES" << endl;


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

    cout << "chosen move:" << endl;
    cout << "(" << move.getFromCoordinates().first << ", " << move.getFromCoordinates().second << ")   ->   ";
    cout << "(" << move.getToCoordinates().first << ", " << move.getToCoordinates().second << ")" << endl;

    
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

bool Player::computer2Move(Game* game, Board& board, bool isWhiteTurn) {
    static std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> white_opening_moves = {
        {{6, 4}, {4, 4}}, // e2 to e4
        {{7, 6}, {5, 5}}, // g1 to f3
        {{7, 1}, {5, 2}}  // b1 to c3
    };

    static std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> black_opening_moves = {
        {{1, 3}, {3, 3}}, // d7 to d5
        {{0, 1}, {2, 2}}, // b8 to c6
        {{0, 6}, {2, 5}}  // g8 to e6
    };

    static size_t white_move_index = 0;
    static size_t black_move_index = 0;

    std::vector<Move> possible_moves = board.getPossibleMoves(isWhiteTurn);

    if (possible_moves.empty()) {
        std::cout << "No way it's empty" << std::endl;
        return false; // No valid moves
    }

    Move move = possible_moves[rand() % possible_moves.size()]; // Initialize with a random move

    bool move_found = false;

    if (isWhiteTurn && white_move_index < white_opening_moves.size()) {
        auto [from, to] = white_opening_moves[white_move_index];
        Square* from_square = &board.getSquare(from.first, from.second);
        Square* to_square = &board.getSquare(to.first, to.second);
        Piece* piece = from_square->getPiece();

        // Check if the opening move is in possible_moves
        for (const auto& possible_move : possible_moves) {
            if (possible_move.getStartingCoord() == from_square &&
                possible_move.getDestinationCoord() == to_square) {
                move = Move(from_square, to_square, piece, board);
                white_move_index++;
                move_found = true;
                break;
            }
        }
    } else if (!isWhiteTurn && black_move_index < black_opening_moves.size()) {
        auto [from, to] = black_opening_moves[black_move_index];
        Square* from_square = &board.getSquare(from.first, from.second);
        Square* to_square = &board.getSquare(to.first, to.second);
        Piece* piece = from_square->getPiece();

        // Check if the opening move is in possible_moves
        for (const auto& possible_move : possible_moves) {
            if (possible_move.getStartingCoord() == from_square &&
                possible_move.getDestinationCoord() == to_square) {
                move = Move(from_square, to_square, piece, board);
                black_move_index++;
                move_found = true;
                break;
            }
        }
    }

    if (!move_found) {
        move = possible_moves[rand() % possible_moves.size()];
    }

    std::cout << "chosen move:" << std::endl;
    std::cout << "(" << move.getFromCoordinates().first << ", " << move.getFromCoordinates().second << ")   ->   ";
    std::cout << "(" << move.getToCoordinates().first << ", " << move.getToCoordinates().second << ")" << std::endl;

    if (game->makeMove(move)) {
        // After making the move, check for check or checkmate
        bool king_in_check = game->getBoard().isCheck(isWhiteTurn);
        bool king_in_checkmate;

        if (king_in_check) {
            king_in_checkmate = game->getBoard().isCheckmate(isWhiteTurn);
            if (isWhiteTurn) {
                std::cout << "The white king is in check!" << std::endl;
                if (king_in_checkmate) std::cout << "The white king is in checkmate" << std::endl;
            } else {
                std::cout << "The black king is in check!" << std::endl;
                if (king_in_checkmate) std::cout << "The black king is in checkmate" << std::endl;
            }
        }
        // Update promotion if needed
        game->getBoardModifiable()->pawnGettingPromoted(!isWhiteTurn);
        return true;
    }
    return false;
}


bool Player::computer3Move(Game* game, Board& board, bool isWhiteTurn) {
    // Example: Move that captures the highest value piece
    vector<Move> possible_moves = board.getPossibleMoves(isWhiteTurn);
    cout << "1" << endl;
    if (possible_moves.empty()) {
        return false;
    }
    cout << "2" << endl;
    Move best_move = possible_moves[0];  // Initialize with the first move
    int best_value = -9999;
    for (const Move& move : possible_moves) {
        int move_value = evaluateMove(board, move);
        if (move_value > best_value) {
            best_value = move_value;
            best_move = move;
        }
    }
    cout << "3" << endl;

    if (game->makeMove(best_move)) {
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

int Player::evaluateMove(const Board& board, const Move& move) {
    // Simple piece values
    const int PAWN_VALUE = 1;
    const int KNIGHT_VALUE = 3;
    const int BISHOP_VALUE = 3;
    const int ROOK_VALUE = 5;
    const int QUEEN_VALUE = 9;
    const int KING_VALUE = 0; // King value can be high negative if needed

    // Piece values map
    unordered_map<char, int> piece_values = {
        {'P', PAWN_VALUE}, {'p', -PAWN_VALUE},
        {'N', KNIGHT_VALUE}, {'n', -KNIGHT_VALUE},
        {'B', BISHOP_VALUE}, {'b', -BISHOP_VALUE},
        {'R', ROOK_VALUE}, {'r', -ROOK_VALUE},
        {'Q', QUEEN_VALUE}, {'q', -QUEEN_VALUE},
        {'K', KING_VALUE}, {'k', -KING_VALUE}
    };

    // Get the starting and ending coordinates of the move
    const pair<int, int> from_coordinates = move.getFromCoordinates();
    const pair<int, int> to_coordinates = move.getToCoordinates();

    // Get the piece being moved and its value
    const Piece* moving_piece = move.getPiece();
    if (!moving_piece) {
        cerr << "Error: moving_piece is null" << endl;
        return -9999; // or some other low value to indicate an invalid move
    }

    char moving_piece_symbol = moving_piece->getSymbol();
    int move_value = piece_values[moving_piece_symbol];

    // Check the destination square
    Square to_square = board.getSquare(to_coordinates.first, to_coordinates.second);
    if (to_square.isOccupied()) {
        const Piece* destination_piece = to_square.getPiece();
        if (destination_piece) {
            char destination_piece_symbol = destination_piece->getSymbol();
            // If the destination square is occupied, adjust the move value based on the piece being captured
            move_value += piece_values[destination_piece_symbol];
        }
    }

    return move_value;
}




// // Minimax function
// int minimax(Game* game, Board& board, bool isWhiteTurn, int depth, bool isMaximizingPlayer) {
//     if (depth == 0 || game->isGameOver()) {
//         return evaluateBoard(board, isWhiteTurn); // Evaluate the board state
//     }

//     vector<Move> possible_moves = board.getPossibleMoves(isWhiteTurn);
//     if (possible_moves.empty()) {
//         return isMaximizingPlayer ? NEG_INF : INF; // No moves means a bad position for the player
//     }

//     int bestValue = isMaximizingPlayer ? NEG_INF : INF;

//     for (const Move& move : possible_moves) {
//         Board newBoard = board; // Create a new board state
//         game->makeMove(move); // Apply the move
//         int value = minimax(game, newBoard, !isWhiteTurn, depth - 1, !isMaximizingPlayer); // Recursively evaluate
//         game->undoMove(move); // Undo the move

//         if (isMaximizingPlayer) {
//             bestValue = std::max(bestValue, value);
//         } else {
//             bestValue = std::min(bestValue, value);
//         }
//     }

//     return bestValue;
// }

// // Computer Move function using Minimax
// Move Player::computer3Move(Game* game, Board& board, bool isWhiteTurn) {
//     vector<Move> possible_moves = board.getPossibleMoves(isWhiteTurn);

//     if (possible_moves.empty()) {
//         return Move(nullptr, nullptr, nullptr, board); // Return an invalid move if no moves are possible
//     }

//     Move best_move = possible_moves[0];
//     int best_value = NEG_INF;

//     for (const Move& move : possible_moves) {
//         Board newBoard = board; // Create a new board state
//         game->makeMove(move); // Apply the move
//         int move_value = minimax(game, newBoard, !isWhiteTurn, MAX_DEPTH - 1, false); // Evaluate the move
//         game->undoMove(move); // Undo the move

//         if (move_value > best_value) {
//             best_value = move_value;
//             best_move = move;
//         }
//     }

//     return best_move;
// }

// // Evaluation function (example, modify as needed)
// int evaluateBoard(const Board& board, bool isWhiteTurn) {
//     // Simple example: evaluate the board based on piece values
//     int score = 0;
//     for (const auto& piece : board.getAllPieces()) {
//         if (piece->getColour() == isWhiteTurn) {
//             score += getPieceValue(piece->getSymbol());
//         } else {
//             score -= getPieceValue(piece->getSymbol());
//         }
//     }
//     return score;
// }

// // Helper function to get the value of a piece
// int getPieceValue(char symbol) {
//     switch (symbol) {
//         case 'P': return 1;
//         case 'N': return 3;
//         case 'B': return 3;
//         case 'R': return 5;
//         case 'Q': return 9;
//         case 'K': return 0;
//         default: return 0;
//     }
// }


// // Move Player::computer4Move(Board& board) {
// //     // Even more advanced logic, such as minimax algorithm with a certain depth
// //     // Implement the logic here
// //     return Move();
// // }
