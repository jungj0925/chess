#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H

class Square;

#include "observer.h"
#include "board.h"

class TextObserver : public Observer {
    Board* board;

public:
    TextObserver(Board* board);
    void notify() override;
};

#endif // TEXTOBSERVER_H

