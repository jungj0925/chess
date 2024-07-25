#include "../include/game.h"

Game::Game(string p1, string p2, bool manual_setup) {
     // Create Players
    Player* player1 = nullptr;
    Player* player2 = nullptr;

    // Create Player objects based on the input strings
    if (p1 == "human") {
        player1 = new Player(p1, "white");
    } else if (p1.find("computer") != std::string::npos) {
     //    int level = p1.back() - '0'; // Extract the level from "computer[X]"
        player1 = new Player(p1, "white");
    } else {
        throw std::invalid_argument("Invalid player type for p1");
    }

    if (p2 == "human") {
        player2 = new Player(p1, "black");
    } else if (p2.find("computer") != std::string::npos) {
     //    int level = p2.back() - '0'; // Extract the level from "computer[X]"
        player2 = new Player(p2, "black");
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

Player& Game::getCurrentPlayer() {
     return *currentplayer;
}

const Board& Game::getBoard() {
     return *board;
}

bool Game::isWhiteTurn() {
     return (currentplayer->getColour() == "white" ? true : false);
}

bool Game::makeMove(Move& move) {
    // // Get the current player and their opponent
    // Player currentPlayer = getCurrentPlayer();
    // // Retrieve the starting and destination squares from the move
    // Square* fromSquare = move.getStartingCoord();
    // Square* toSquare = move.getDestinationCoord();

    // // Move the piece on the board
    // Piece* piece = fromSquare->getPiece();
    // if (piece != nullptr) {
    //     piece->move(toSquare);
    //  //    // Check for check or checkmate
    //  //    if (getBoard().isCheckmate(currentPlayer->getColour())) {
    //  //        std::cout << "Checkmate! " << currentPlayer->getColour() << " loses." << std::endl;
    //  //        // End the game or declare the result
    //  //    } else if (getBoard().isCheck(currentPlayer->getColour())) {
    //  //        std::cout << "Check!" << std::endl;
    //  //    }

    //     // Switch the turn to the other player
    //     switchPlayer();

    //     // Update the game history if necessary
    //     // gameHistory.addMove(move);
    // } else {
    //     std::cout << "No piece on the starting square." << std::endl;
    // }
    Square* fromSquare = move.getStartingCoord();
    Square* toSquare = move.getDestinationCoord();
    Piece* piece = fromSquare->getPiece();
    if (piece && piece->validMove(*toSquare, *board)) {
        piece->move(toSquare, *board);
        // board->getSquare(toSquare->getCoordinates().first, toSquare->getCoordinates().second).setPiece(piece);
        // fromSquare->setPiece(nullptr);
    } else {
        std::cout << "Invalid move" << std::endl;
        return false;
    }
    return true;
}


Board* Game::getBoardModifiable() {
    return board;
}


