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

pair<bool, bool> Player::makeMove(Game* game, Board& board, bool isWhiteTurn) {
    switch (type) {
        case PlayerType::HUMAN: {
            pair<bool, bool> valid_move_and_checkmate = humanMove(game, board, isWhiteTurn);
            return valid_move_and_checkmate;
        }
        case PlayerType::COMPUTER1: {
            pair<bool, bool> valid_move_and_checkmate = computer1Move(game, board, isWhiteTurn);
            return valid_move_and_checkmate;
            // return computer1Move(game, board, isWhiteTurn);
        }
        case PlayerType::COMPUTER2: {
            pair<bool, bool> valid_move_and_checkmate = computer2Move(game, board, isWhiteTurn);
            return valid_move_and_checkmate;
            // return computer2Move(game, board, isWhiteTurn);
        }
        case PlayerType::COMPUTER3: {
            pair<bool, bool> valid_move_and_checkmate = computer3Move(game, board, isWhiteTurn);
            return valid_move_and_checkmate;
            // return computer3Move(game, board, isWhiteTurn);
        }
        case PlayerType::COMPUTER4: {
            pair<bool, bool> valid_move_and_checkmate = computer4Move(game, board, isWhiteTurn);
            return valid_move_and_checkmate;
            // return computer4Move(game, board, isWhiteTurn);
        }
        default:
            return make_pair(false, false);
    }
}

pair<bool, bool> Player::humanMove(Game* game, Board& board, bool isWhiteTurn) {
    string from, to, promotionPiece;
    cin >> from >> to;

    // Check for correct length of input
    if (from.length() != 2 && to.length() != 2) {
        cout << "Invalid coordinate given, try again" << endl;
        return make_pair(false, false);
    }  

    if (!('a' <= from[0] && from[0] <= 'h' && 
            '1' <= from[1] && from[1] <= '8' && 
            'a' <= to[0] && to[0] <= 'h' && 
            '1' <= to[1] && to[1] <= '8')) {
        cout << "Invalid coordinate given, try again" << endl;
        return make_pair(false, false);
    }


    auto f = new Square(from, game->getBoard());
    auto t = new Square(to, game->getBoard());

    if (!f->getPiece()) {
        cout << "No piece in square, try again" << endl;
        return make_pair(false, false);
    }


    if ((!islower(f->getPiece()->getSymbol()) && !isWhiteTurn) || (islower(f->getPiece()->getSymbol()) && isWhiteTurn)) {
        cout << "It's not your turn rn" << endl;
        return make_pair(false, false);
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

                if (king_in_checkmate) {
                    cout << "The white king is in checkmate" << endl;
                    return make_pair(true, true);
                }
            } else {
                cout << "The black king is in check!" << endl;

                if (king_in_checkmate) {
                    cout << "The black king is in checkmate" << endl;
                    return make_pair(true, true);
                }
            }
        }

        // TESTING
        game->getBoardModifiable()->pawnGettingPromoted(!isWhiteTurn);
        return make_pair(true, false);
    }

    return make_pair(false, false);
}


// HELLO ANDY JUNG
bool Player::computer1Move(Game* game, Board& board, bool isWhiteTurn) {
    vector<Move> possible_moves = board.getPossibleMoves(isWhiteTurn);

    if (possible_moves.empty()) {
        cout << "No way it's empty" << endl;
        return false; // No valid moves
    }

    // Select a random move
    std::srand(std::time(nullptr));
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
    std::srand(std::time(nullptr));

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
    std::vector<Move> possible_moves = board.getPossibleMoves(isWhiteTurn);
    if (possible_moves.empty()) {
        return false;
    }

    // Seed the random number generator
    std::srand(std::time(nullptr));

    // 30% chance to choose a random move
    if (std::rand() % 100 < 40) {
        Move move = possible_moves[std::rand() % possible_moves.size()];
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

    // If not a random move, find the best move as usual
    Move best_move = possible_moves[0];  // Initialize with the first move
    int best_value = -9999;
    for (const Move& move : possible_moves) {
        int move_value = evaluateMove(board, move);
        if (move_value > best_value) {
            best_value = move_value;
            best_move = move;
        }
    }

    if (game->makeMove(best_move)) {
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

bool Player::computer4Move(Game* game, Board& board, bool isWhiteTurn) {
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

    static int white_move_index = 0;
    static int black_move_index = 0;

    std::vector<Move> possible_moves = board.getPossibleMoves(isWhiteTurn);

    if (possible_moves.empty()) {
        std::cout << "No way it's empty" << std::endl;
        return false; // No valid moves
    }

    // Seed the random number generator
    std::srand(std::time(nullptr));

    Move move = possible_moves[0];  // Initialize with the first move

    bool move_found = false;

    // Random probability for choosing opening move or random move
    int chance = std::rand() % 100;

    if (isWhiteTurn && white_move_index < white_opening_moves.size() && chance < 30) {
        // 30% chance to use opening move
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
    } else if (!isWhiteTurn && black_move_index < black_opening_moves.size() && chance < 30) {
        // 30% chance to use opening move
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
    } else if (chance < 50) {
        // 20% chance to choose a random move
        move = possible_moves[std::rand() % possible_moves.size()];
        move_found = true;
    }

    if (!move_found) {
        // 50% chance to choose the best move
        int best_value = -9999;
        for (const Move& m : possible_moves) {
            int move_value = evaluateMove(board, m);
            if (move_value > best_value) {
                best_value = move_value;
                move = m;
            }
        }
    }

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
