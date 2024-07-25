#include "textObserver.h"
#include "../include/square.h"
#include <iostream>

TextObserver::TextObserver(Board* board) : board(board) {}

void TextObserver::notify() {
    std::cout << "Board updated. Current state:" << std::endl;

    // Unicode characters for the chess board
    char whiteSquare = '-'; // □
    char blackSquare = '#'; // ■

    for (int i = 7; i >= 0; --i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 8; ++j) {
            // const Square& square = board->getSquare(i, j);
            if (board->getSquare(j, i).isOccupied()) {
                // const Piece* piece = board->getSquare(i, j).getPiece(); // Get the piece
                std::cout << board->getSquare(j, i).getPiece()->getSymbol() << " "; // Dereference piece to call getSymbol()
            } else {
                // Alternate squares between white and black
                std::cout << ((i + j) % 2 == 0 ? blackSquare : whiteSquare) << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  a b c d e f g h" << std::endl;
}
