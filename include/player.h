#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"
#include "board.h"
#include "game.h"
#include "move.h"  // Include the Move header file
#include <string>
#include <vector>

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
    bool makeMove(Game* game, Board& board, bool isWhiteTurn);

private:
    bool humanMove(Game* game, Board& board, bool isWhiteTurn);
    bool computer1Move(Game* game, Board& board, bool isWhiteTurn);
    Move computer2Move(Board& board);
    Move computer3Move(Board& board);
    Move computer4Move(Board& board);
};

#endif
