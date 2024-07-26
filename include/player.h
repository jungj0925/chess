#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"
#include "board.h"
#include "game.h"
#include "move.h"  // Include the Move header file
#include <string>
#include <vector>
#include <limits>

class Game;

using namespace std;

enum class PlayerType { HUMAN, COMPUTER1, COMPUTER2, COMPUTER3, COMPUTER4 };

class Player {
    string name;
    string colour;
    vector<Piece*> dead_pieces;
    PlayerType type;

public:
    Player(const string& name, const string& colour);
    ~Player() {};
    string& getColour();
    PlayerType getType() const;
    pair<bool, bool> makeMove(Game *game, Board &board, bool isWhiteTurn);

private:
    // First: valid_move, Second: checkmate 
    pair<bool, bool> humanMove(Game* game, Board& board, bool isWhiteTurn);
    pair<bool, bool> computer1Move(Game *game, Board &board, bool isWhiteTurn);
    pair<bool, bool> computer2Move(Game *game, Board &board, bool isWhiteTurn);
    pair<bool, bool> computer3Move(Game *game, Board &board, bool isWhiteTurn);
    pair<bool, bool> computer4Move(Game *game, Board &board, bool isWhiteTurn);

    Move minimax(Game* game, Board& board, bool isWhiteTurn);
    vector<Move> generateAllPossibleMoves(Game* game, Board& board, bool isWhiteTurn);


    int evaluateBoard(const Board& board, bool isWhiteTurn);
    int evaluateMove(const Board& board, const Move& move);
};

#endif
