#include "../include/board.h"
#include "../include/move.h"

// col = x
// row = y

Board::Board() : the_board(8, vector<Square *>(8, nullptr)) {
    // Init all the Squares
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            the_board[row][col] = new Square(col, row);
        }
    }
    blackKing = nullptr;
    whiteKing = nullptr;
}

void Board::setUp() {
    // Place Black Team Pieces
    the_board[7][0]->setPiece(new Rook(the_board[7][0], "black", 'r'));
    the_board[7][1]->setPiece(new Knight(the_board[7][1], "black", 'n'));
    the_board[7][2]->setPiece(new Bishop(the_board[7][2], "black", 'b'));
    the_board[7][3]->setPiece(new Queen(the_board[7][3], "black", 'q'));

    King * king1 = new King(the_board[7][4], "black", 'k');
    blackKing = king1;
    the_board[7][4]->setPiece(king1);
    the_board[7][5]->setPiece(new Bishop(the_board[7][5], "black", 'b'));
    the_board[7][6]->setPiece(new Knight(the_board[7][6], "black", 'n'));
    the_board[7][7]->setPiece(new Rook(the_board[7][7], "black", 'r'));

    for (int col = 0; col < 8; ++col) the_board[6][col]->setPiece(new Pawn(the_board[6][col], "black", 'p'));


    // Place White Team Pieces

    the_board[0][0]->setPiece(new Rook(the_board[0][0], "white", 'R'));
    the_board[0][1]->setPiece(new Knight(the_board[0][1], "white", 'N'));
    the_board[0][2]->setPiece(new Bishop(the_board[0][2], "white", 'B'));
    the_board[0][3]->setPiece(new Queen(the_board[0][3], "white", 'Q'));

    King * king2 = new King(the_board[0][4], "white", 'K');
    whiteKing = king2;
    the_board[0][4]->setPiece(king2);
    the_board[0][5]->setPiece(new Bishop(the_board[0][5], "white", 'B'));
    the_board[0][6]->setPiece(new Knight(the_board[0][6], "white", 'N'));
    the_board[0][7]->setPiece(new Rook(the_board[0][7], "white", 'R'));

    for (int col = 0; col < 8; ++col) the_board[1][col]->setPiece(new Pawn(the_board[1][col], "white", 'P'));
}

void Board::placePiece(char piece, string position) const {
    char col = position[0] - 'a';
    char row = position[1] - '1';

    // Set up pawns
    if (piece == 'p') {
        the_board[row][col]->setPiece(new Pawn(the_board[row][col], "black", piece));
        if (row != 6) {
            the_board[row][col]->getPiece()->setFirstMove(false);
        }
    }
    if (piece == 'P') {
        the_board[row][col]->setPiece(new Pawn(the_board[row][col], "white", piece));
        if (row != 1) {
            the_board[row][col]->getPiece()->setFirstMove(false);
        }
    }
    // Set up rook
    if (piece == 'r') {
        the_board[row][col]->setPiece(new Rook(the_board[row][col], "black", piece));
        if ((row != 7) && ((col != 0) || (col != 7))) {
            the_board[row][col]->getPiece()->setFirstMove(false);
        }
    }
    if (piece == 'R') {
        the_board[row][col]->setPiece(new Rook(the_board[row][col], "white", piece));
        if ((row != 0) && ((col != 0) || (col != 7))) {
            the_board[row][col]->getPiece()->setFirstMove(false);
        }
    }

    // Set up Knights
    if (piece == 'n') the_board[row][col]->setPiece(new Knight(the_board[row][col], "black", piece));
    if (piece == 'N') the_board[row][col]->setPiece(new Knight(the_board[row][col], "white", piece));

    // Set up Bishops
    if (piece == 'b') the_board[row][col]->setPiece(new Bishop(the_board[row][col], "black", piece));
    if (piece == 'B') the_board[row][col]->setPiece(new Bishop(the_board[row][col], "white", piece));
    
    // Set up Queen
    if (piece == 'q') the_board[row][col]->setPiece(new Queen(the_board[row][col], "black", piece));
    if (piece == 'Q') the_board[row][col]->setPiece(new Queen(the_board[row][col], "white", piece));

    // Set up King
    if (piece == 'k') {
        the_board[row][col]->setPiece(new King(the_board[row][col], "black", piece));
        if ((row != 7) && (col != 4)) {
            the_board[row][col]->getPiece()->setFirstMove(false);
        }
    }
    if (piece == 'K') {
        the_board[row][col]->setPiece(new King(the_board[row][col], "white", piece));
        if ((row != 0) && (col != 4)) {
            the_board[row][col]->getPiece()->setFirstMove(false);
        }
    }}

void Board::removePiece(string position) const {
    char col = position[0] - 'a';
    char row = position[1] - '1';

    the_board[row][col]->removePiece();
}

// bool Board::isCheck(bool isWhite) {
//     // Find the king of the player
//     Piece* king = nullptr;
//     for (int x = 0; x < 8; ++x) {
//         for (int y = 0; y < 8; ++y) {
//             Square* square = board.getSquare(x, y);
//             Piece* piece = square->getPiece();
//             if (piece != nullptr && ((isWhite && piece->getSymbol() == 'K') || (!isWhite && piece->getSymbol() == 'k'))) {
//                 king = piece;
//                 break;
//             }
//         }
//         if (king != nullptr) break;
//     }

//     if (king == nullptr) return false; // King not found, invalid state

//     // Check if any opponent's piece can attack the king
//     for (int x = 0; x < 8; ++x) {
//         for (int y = 0; y < 8; ++y) {
//             Square square = getSquare(x, y);
//             Piece* piece = square.getPiece();
//             if (piece != nullptr && islower(piece->getSymbol()) != isWhite) {
//                 // Check if the piece can move to the king's position
//                 if (piece->validMove(*king->getCurrentPosition(), board)) {
//                     return true;
//                 }
//             }
//         }
//     }

//     return false;
// }

void Board::movePiece(Move &move) {
    Square *start = move.getStartingCoord();
    Square *destination = move.getDestinationCoord();

    Piece *piece = start->getPiece();

    piece->move(destination, *this);
}

Board::~Board() {
    // Clean up memorrow if necessary
    for (auto row : the_board) {
        for (auto square : row) {
            delete square;
        }
    }
}

void Board::display() const {
    notifyObservers(); // Notify observers when rendering happens
}

bool Board::isValidPosition(int col, int row) const {
    return col >= 0 && col < 8 && row >= 0 && row < 8;
}

Square& Board::getSquare(int col, int row) const {
    return *the_board[row][col];
}

bool Board::isCheck(bool isWhiteTurn) const {
    cout << "IS CHECKING" << endl;

    Square* king_position;
    
    // isWhiteTurn gets changed before verifying for check & checkmate
    if (isWhiteTurn) {
        king_position = whiteKing->getCurrentPosition();
    } else {
        king_position = blackKing->getCurrentPosition();
    }

    // Debug prints
    std::cout << "Checking if king is in check for " << (isWhiteTurn ? "white" : "black") << " king.\n";
    std::cout << "King position: (" << king_position->getCoordinates().first << ", " << king_position->getCoordinates().second << ")\n";

    if (king_position == nullptr) {
        throw std::runtime_error("King position is invalid");
    }

    for (int col = 0; col < 8; ++col) {
        for (int row = 0; row < 8; ++row) {
            Piece* piece = getSquare(col, row).getPiece();
            if (piece != nullptr) {
                // std::cout << "Checking piece at (" << col << ", " << row << ") of type " << piece->getSymbol() << "\n";
                // Check for piece
                if (islower(piece->getSymbol()) != islower(king_position->getPiece()->getSymbol())) {
                    // Check if the piece can possibly capture the king
                    if (piece->validMove(*king_position, *this)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

vector<Square> Board::getPathToKing(Square &attacker_square, Square &king_square) const {
    vector<Square> path;
    int difference_in_x = attacker_square.getCoordinates().first - king_square.getCoordinates().first;
    int difference_in_y = attacker_square.getCoordinates().second - king_square.getCoordinates().second;

    int direction_x = (difference_in_x > 0) ? -1 : (difference_in_x < 0) ? 1 : 0;
    int direction_y = (difference_in_y > 0) ? -1 : (difference_in_y < 0) ? 1 : 0;

    int intermediate_x = attacker_square.getCoordinates().first + direction_x;
    int intermediate_y = attacker_square.getCoordinates().second + direction_y;

    while (intermediate_x != king_square.getCoordinates().first || intermediate_y != king_square.getCoordinates().second) {
        path.push_back(getSquare(intermediate_x, intermediate_y));
        intermediate_x += direction_x;
        intermediate_y += direction_y;
    }

    return path;
}

bool Board::isCheckmate(bool isWhiteTurn) const {
    cout << "IS CHECKING" << endl;

    Square* king_position;
    King* king;

    // isWhiteTurn gets changed before verifying for check & checkmate
    if (isWhiteTurn) {
        king_position = whiteKing->getCurrentPosition();
        king = dynamic_cast<King*>(whiteKing);
    } else {
        king_position = blackKing->getCurrentPosition();
        king = dynamic_cast<King*>(blackKing);
    }

    // Debug prints
    std::cout << "Checking if king is in check for " << (isWhiteTurn ? "white" : "black") << " king.\n";
    std::cout << "King position: (" << king_position->getCoordinates().first << ", " << king_position->getCoordinates().second << ")\n";

    if (king_position == nullptr) {
        throw std::runtime_error("King position is invalid");
    }

    // Check for any safe squares the king can move to
    vector<Square> possible_moves = king->getPossibleMoves(*this);

    cout << "NUmber of possible moves: " << possible_moves.size() << endl;

    vector<Square> unsafe_moves;

    for (int col = 0; col < 8; ++col) {
        for (int row = 0; row < 8; ++row) {
            Square& current_square = getSquare(col, row);
            Piece *piece = current_square.getPiece();

            // Check for a valid piece
            if (piece != nullptr ) {
                // Check for opposition piece
                if (islower(piece->getSymbol()) != islower(king->getSymbol())) {
                    
                    // Check for every move that the king can make
                    for (Square& move : possible_moves) {

                    // cout << "IN INNER LOOP" << endl;

                        if (piece->validMove(*king_position, *this)) {

                            // vector<Square> path_to_king = getPathToKing(current_square, *king_position);

                            unsafe_moves.emplace_back(move);
                        }
                    }


                }
            }
        }
    }

    if (unsafe_moves.size() != possible_moves.size()) {
        // Found a safe move for the king
        return false;
    }

    for (int col = 0; col < 8; ++col) {
        for (int row = 0; row < 8; ++row) {
            Square& current_square = getSquare(col, row);
            Piece *piece = current_square.getPiece();

            // Check for a valid piece
            if (piece != nullptr ) {
                // Check for opposition piece
                if (islower(piece->getSymbol()) != islower(king->getSymbol())) {
                    // for (Square& move : possible_moves) {

                    // cout << "IN INNER LOOP" << endl;

                    if (piece->validMove(*king_position, *this)) {

                        vector<Square> path_to_king = getPathToKing(current_square, *king_position);

                        // illegal_moves.emplace_back(move);

                        // Check if any piece can move to block the path or capture the attacker
                        for (int c = 0; c < 8; ++c) {
                            for (int r = 0; r < 8; ++r) {
                                Piece* defending_piece = getSquare(c, r).getPiece();

                                if (defending_piece != nullptr) {
                                    if (islower(defending_piece->getSymbol()) != islower(king->getSymbol())) {
                                        for (Square& block_square : path_to_king) {
                                        if (defending_piece->validMove(block_square, *this)) {
                                            // Found a move that can block the check
                                            return false;
                                        }
                                    }
                                    // Check if the defending piece can capture the attacker
                                    if (defending_piece->validMove(current_square, *this)) {
                                        return false;
                                    }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

void Board::pawnGettingPromoted(bool is_white_turn) {
    // Set defaults to white turn
    vector<char> captured_pieces = getCapturedPieces().first;
    int row = 7;
    char pawn_symbol = 'P'; 

    // Get all the dead pieces
    if (!is_white_turn) {
        captured_pieces = getCapturedPieces().second;
        row = 0;
        pawn_symbol = 'p';
    }

    char promoted_pawn;

    cout << getCapturedPieces().first.size() << endl;
    for (auto p : captured_pieces) cout << p << ", ";

    // DEBUGGING
    auto cp = getCapturedPieces().second;
    cout << getCapturedPieces().second.size() << endl;
    for (auto p : cp) cout << p << ", ";

    // Check for pawn getting promoted
    for (int col = 0; col < 8; ++col) {
        Piece *piece = getSquare(col, row).getPiece();

        // Check if piece exists
        if (piece) {
            
            // Verify it is your pawn
            if (piece->getSymbol() == pawn_symbol) {

                
                cout << "These are your promotion options : ";
                for (auto piece : captured_pieces) cout << piece << "   ";
                cout << "\n";

                cout << "Which piece would you like to promote your pawn to (type the character below): " << endl;
                // cout << "(";
                // for (auto piece : captured_pieces) cout << piece << ", ";
                // cout << ")" << endl;

                // cin >> promoted_pawn;
                while (true) {
                    cin >> promoted_pawn;
                    if (isPresent(captured_pieces, promoted_pawn)) {
                        cout << "Your pawn has been promoted!" << endl;
                        break;
                    } else {
                        cout << "Please enter a valid peice" << endl;
                    }
                }


                // Remove Pawn & Place new piece
                getSquare(col, row).setPiece(nullptr);

                placePiece(promoted_pawn, coordinatesToPosition(col, row));
            }
        }
    }
}

// Function to check if a character is present in the vector
bool Board::isPresent(const vector<char>& vec, char value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

string Board::coordinatesToPosition(int x, int y) {
    char column = 'a' + x;
    char row = '1' + y;
    
    // Create the position string
    return string(1, column) + row;
}

// First is white
// Second is black
pair<vector<char>, vector<char>> Board::getCapturedPieces() const {

    vector<char> all_pieces = {'r', 'n', 'b', 'q', 'b', 'n', 'r',
                                'R', 'N', 'B', 'Q', 'B', 'N', 'R',};

    vector<char> alive_pieces;


    for (int col = 0; col < 8; ++col) {
        for (int row = 0; row < 8; ++row) {
            Square& current_square = getSquare(col, row);
            Piece *piece = current_square.getPiece();

            // Check for a valid piece
            if (piece != nullptr ) {
                // Check for opposition piece
                char peice_symbol = piece->getSymbol();
                // cout << "PIECE SYMBOL: " << peice_symbol << endl;
                if (tolower(peice_symbol) != 'p' && tolower(peice_symbol) != 'k') {
                    alive_pieces.emplace_back(peice_symbol);
                }
            }
        }
    }

    // Find the difference between the two to find captured pieces
    // cout << "("; 
    // for (auto p : alive_pieces) cout << p << ", ";
    // cout << ")" << endl;

    // cout << alive_pieces.size() << endl;

    // Sort both vectors
    std::sort(all_pieces.begin(), all_pieces.end());
    std::sort(alive_pieces.begin(), alive_pieces.end());

    // Find the difference between the two to find captured pieces
    vector<char> captured_pieces;
    vector<char> white_captured_pieces;
    vector<char> black_captured_pieces;
    set_difference(all_pieces.begin(), all_pieces.end(), alive_pieces.begin(), alive_pieces.end(), back_inserter(captured_pieces));

    // cout << "(";
    for (auto p : captured_pieces) {
        // cout << p << ", ";

        if (islower(p)) black_captured_pieces.emplace_back(p);
        else white_captured_pieces.emplace_back(p);
    }
    // cout << ")" << endl;



    cout << "WHITE CAPTURED PIECES: ";
    for (auto p : white_captured_pieces) {
        cout << p << ", ";
    }

    cout << "Black CAPTURED PIECES: ";
    for (auto p : black_captured_pieces) {
        cout << p << ", ";
    }

    cout << "\n";

    return make_pair(white_captured_pieces, black_captured_pieces);
}


std::vector<Move> Board::getPossibleMoves(bool isWhiteTurn) {
    std::vector<Move> result;

    // Iterate through each square on the board
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            Square& square = getSquare(x, y);
            Piece* piece = square.getPiece();

            if (piece == nullptr) {
                continue;
            }

            // Check if the square has a piece and if it's the current player's piece
            if (((isWhiteTurn && isupper(piece->getSymbol())) || (!isWhiteTurn && islower(piece->getSymbol())))) {
                std::vector<Square> possibleSquares = piece->getPossibleMoves(*this);

                // Iterate through each possible destination square
                for (Square& toSquare : possibleSquares) {
                    // Construct a move and add it to the result vector
                    result.emplace_back(&square, &toSquare, piece, *this);
                }
            }
        }
    }

    return result;
}
