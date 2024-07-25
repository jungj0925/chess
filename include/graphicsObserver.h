#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H

#include "observer.h"
#include "studio.h"
#include "window.h"
#include "board.h"

class GraphicsObserver : public Observer {
    Board *board;
    Xwindow xw;

public:
    GraphicsObserver(Board *board);
    void notify() override;
};

#endif // GRAPHICSOBSERVER_H


