#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <memory>

#include "board.h"
#include "player.h"
#include "move.h"

class Player;

// using namespace std;

class Game { 
     Board* board;
     Player* currentplayer;
     Player* blackplayer;
     Player* whiteplayer;
     Piece* whiteKing;
     Piece* blackKing;

     public:
          Game(string p1, string p2, bool manual_setup);
          ~Game() { delete board; };

          bool isCheck(const std::string& colour);
          bool isCheckmate(const std::string& colour);
          bool isMoveLegal(Square* start, Square* end, const std::string& colour);
          bool isGameOver();

          Player* getCurrentPlayer();
          const Board& getBoard();

          Board& getBoard2() {
               return *board;
          }

          void changeTurns();

          Board* getBoardModifiable();
          bool makeMove(Move& move);

          bool isWhiteTurn();
};

#endif
