#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"
#include "board.h"
#include <string>
#include <vector>

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
    bool makeMove(Move& move, Board& board);
};

#endif
