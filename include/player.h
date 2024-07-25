#ifndef PLAYER_H
#define PLAYER_H

#include "piece.h"
#include "board.h"
#include "move.h"  // Include the Move header file
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

private:
    bool humanMove(Move& move, Board& board);
    Move computer1Move(Board& board); // computermove is not bool cause we trust them 
    Move computer2Move(Board& board);
    Move computer3Move(Board& board);
    Move computer4Move(Board& board);
};

#endif
