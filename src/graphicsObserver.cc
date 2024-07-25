#include "graphicsObserver.h"
#include <iostream>

GraphicsObserver::GraphicsObserver(Board* board)
    : board(board), window(500, 500) {
}

GraphicsObserver::~GraphicsObserver() {}

void GraphicsObserver::notify() {
    drawBoard();
}

void GraphicsObserver::drawBoard() {
    // Board dimensions
    const int square_size = 60;
    const int board_size = 8;

    // Colors
    const int white_square = Xwindow::White;
    const int black_square = Xwindow::Black;

    // Clear the board
    window.fillRectangle(0, 0, board_size * square_size, board_size * square_size, white_square);
            cout << "Safe" << endl;

    // Draw the squares and pieces
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < board_size; ++j) {
            int x = j * square_size;
            int y = (7 - i) * square_size; // Flip y coordinate for correct drawing order

            // Alternate colors for the squares
            int color = ((i + j) % 2 == 0) ? black_square : white_square;
            window.fillRectangle(x, y, square_size, square_size, color);

            // Draw the piece if there is one
            if (board->getSquare(j, i).isOccupied()) {
                // Get the piece symbol
                char piece = board->getSquare(j, i).getPiece()->getSymbol();

                // Calculate the position for the piece symbol
                float textX = x + square_size / 2;
                float textY = y + square_size / 2;

                // Define the size and padding for the outline rectangle
                float padding = 17.5f; // Reduced padding
                float rectWidth = square_size - 2 * padding; // Adjust width if needed
                float rectHeight = square_size - 2 * padding; // Adjust height if needed

                // Draw the white rectangle for outlining
                window.fillRectangle(textX - rectWidth / 2, textY - rectHeight / 2, rectWidth, rectHeight, white_square);

                // Draw the piece symbol
                window.drawString(textX, textY, std::string(1, piece));
            }
        }
    }

    // Draw row and column labels
    for (int i = 0; i < board_size; ++i) {
        window.drawString(i * square_size + square_size / 2, board_size * square_size + 15, std::string(1, 'a' + i));
        window.drawString(board_size * square_size + 5, (7 - i) * square_size + square_size / 2, std::to_string(i + 1));
    }
}


// void GraphicsObserver::drawSquare(int x, int y) {
//     // Board dimensions
//     const int square_size = 60;

//     // Colors
//     const int white_square = Xwindow::White;
//     const int black_square = Xwindow::Black;

//     int screen_x = x * square_size;
//     int screen_y = (7 - y) * square_size; // Flip y coordinate for correct drawing order

//     // Alternate colors for the squares
//     int color = ((y + x) % 2 == 0) ? black_square : white_square;
//     window.fillRectangle(screen_x, screen_y, square_size, square_size, color);

//     // Draw the piece if there is one
//     if (board->getSquare(x, y).isOccupied()) {
//         char piece = board->getSquare(x, y).getPiece()->getSymbol();
//         // Calculate the position for the piece symbol
//         float textX = x + square_size / 2;
//         float textY = y + square_size / 2;

//         // Define the size and padding for the outline rectangle
//         float padding = 17.5f; // Reduced padding
//         float rectWidth = square_size - 2 * padding; // Adjust width if needed
//         float rectHeight = square_size - 2 * padding; // Adjust height if needed

//         // Draw the white rectangle for outlining
//         window.fillRectangle(textX - rectWidth / 2, textY - rectHeight / 2, rectWidth, rectHeight, white_square);

//         // Draw the piece symbol
//         window.drawString(textX, textY, std::string(1, piece));
//     }
// }
