#ifndef GRAPHICS_OBSERVER_H
#define GRAPHICS_OBSERVER_H

#include "board.h"
#include "window.h"
#include "observer.h"

class GraphicsObserver : public Observer {
    Board* board;
    Xwindow window;
    // std::vector<std::pair<int, int>> updated_squares; // To track updated squares

public:
    GraphicsObserver(Board* board);
    ~GraphicsObserver();

    void notify(); // Called when the board updates
    void drawBoard(); // Draw the entire board
    void drawSquare(int x, int y); // Draw a specific square
};

#endif
