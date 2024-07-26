#include "../include/game.h"

Game::Game(string p1, string p2, bool manual_setup) {
     // Create Players
    Player* player1 = nullptr;
    Player* player2 = nullptr;

    // Create Player objects based on the input strings
    if (p1 == "human") {
        player1 = new Player(p1, "white");
        whiteplayer = player1;
        currentplayer = player1;
    } else if (p1.find("computer") != std::string::npos) {
     //    int level = p1.back() - '0'; // Extract the level from "computer[X]"
        cout << "in game. (comp)" << endl;
        player1 = new Player(p1, "white");
        whiteplayer = player1;
        currentplayer = player1;
    } else {
        throw std::invalid_argument("Invalid player type for p1");
    }

    if (p2 == "human") {
        cout << "in game. (human)" << endl;
        player2 = new Player(p2, "black");
        blackplayer = player2;
    } else if (p2.find("computer") != std::string::npos) {
        cout << "in game. (comp)" << endl;
     //    int level = p2.back() - '0'; // Extract the level from "computer[X]"
        player2 = new Player(p2, "black");
        blackplayer = player2;
    } else {
        throw std::invalid_argument("Invalid player type for p2");
    }

    // whiteplayer = player1;
    // blackplayer = player2;

    // Create Board
    board = new Board();

    // Set up board if not in manual setup mode
    if (!manual_setup) {
        board->setUp();
    }

    // // Initialize current player
    // currentplayer = whiteplayer;
}

Player* Game::getCurrentPlayer() {
     return currentplayer;
}

const Board& Game::getBoard() {
     return *board;
}

bool Game::isWhiteTurn() {
     return (currentplayer->getColour() == "white" ? true : false);
}

bool Game::makeMove(Move& move) {
    // Check if the squares in move are nullptr
    Square* from_square;
    Square* to_square;
    pair<int, int> from_coordinates;
    pair<int, int> to_coordinates;


    if (move.getStartingCoord() == nullptr) {
        from_coordinates = move.getFromCoordinates();
        to_coordinates = move.getToCoordinates();

        from_square = &(board->getSquare(from_coordinates.first, from_coordinates.second));
        to_square = &(board->getSquare(to_coordinates.first, to_coordinates.second));
    } else {
        from_square = move.getStartingCoord();
        to_square = move.getDestinationCoord();
    }

    Piece *piece = from_square->getPiece();

    if (!piece) {
        cout << "Piece does NOT exixt" << endl;
        cout << "(" << from_coordinates.first << ", " << from_coordinates.second << endl;
    }

    if (piece && piece->validMove(*to_square, *board)) {
        piece->move(to_square, *board);

        
        board->addToMoveHistory(move);
        // board->getSquare(toSquare->getCoordinates().first, toSquare->getCoordinates().second).setPiece(piece);
        // fromSquare->setPiece(nullptr);
    } else {
        std::cout << "Invalid move" << std::endl;
        return false;
    }
    return true;
}

void Game::changeTurns() {
    if (currentplayer == whiteplayer) {
        currentplayer = blackplayer;
    } else {
        currentplayer = whiteplayer;
    }
}

Board* Game::getBoardModifiable() {
    return board;
}


