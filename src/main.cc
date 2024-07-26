#include <iostream>
#include <string>

#include "game.h"
#include "board.h"
#include "../include/player.h"
#include "move.h"
#include "square.h"

#include "textObserver.h"
#include "graphicsObserver.h"

using namespace std;

int main() {
     Game* game = nullptr;
     string command;
     bool new_game_started = false;
     bool manual_setup = false;
     bool isWhiteTurn = true;

     

     while (cin >> command) {
          if (command == "game" && !new_game_started) {
               string p1, p2;
               cin >> p1 >> p2;
               game = new Game(p1, p2, manual_setup);
               (*game->getBoardModifiable()).attach(new TextObserver(game->getBoardModifiable()));
               // (*game->getBoardModifiable()).attach(new GraphicsObserver(game->getBoardModifiable()));
               cout << "New game started between " << p1 << " and " << p2 << "." << endl;
               new_game_started = true;
               cout << "It is white's turn" << endl;
               game->getBoard().display();
          } 
          
          else if (command == "resign") {
               if (game != nullptr) {
                    if (game->isWhiteTurn()) {
                         cout << "White resigns. Black wins!" << endl;
                    } else {
                         cout << "Black resigns. White wins!" << endl;
                    }
                    delete game;
                    game = nullptr;
               } else {
                    cout << "No game is currently running." << endl;
               }
          } 
          
          else if (command == "move") {
               if (game != nullptr) {
                    Player* currentPlayer = game->getCurrentPlayer();

                    pair<bool, bool> valid_move_and_checkmate = currentPlayer->makeMove(game, game->getBoard2(), isWhiteTurn);

                    // Check for invalid move
                    if (!valid_move_and_checkmate.first) {
                         continue;
                    }

                    // Check for checkmate
                    else if (valid_move_and_checkmate.second) {
                         if (game->isWhiteTurn()) {
                              cout << "Black is in checkmate. White wins!" << endl;
                         }
                         else {
                              cout << "White is in checkmate. Black wins!" << endl;
                         }
                         delete game;
                         game = nullptr;
                    }
                    
                    else {
                         game->changeTurns();
                         isWhiteTurn = !isWhiteTurn;
                         cout << "It is " << (isWhiteTurn ? "white's" : "black's") << " turn" << endl;
                         game->getBoard().display();
                    }
               } else {
                    cout << "No game is currently running." << endl;
               }
          } 
          
          else if (command == "render") {
               if (game != nullptr) {
                    game->getBoard().display();
               }
          } 
          
          else if (command == "captured_pieces") {
               if (game != nullptr) {
                    pair<vector<char>, vector<char>> captured_pieces = game->getBoard().getCapturedPieces();
                    vector<char> white_captured_pieces = captured_pieces.first;
                    vector<char> black_captured_pieces = captured_pieces.second;

                    cout << "You have captured: ";
                    if (isWhiteTurn) {
                         for (auto piece : black_captured_pieces) cout << piece << "  ";
                    } else {
                         for (auto piece : white_captured_pieces) cout << piece << "  ";
                    }
                    cout << "\n";
               } else {
                    cout << "Game hasn't even started yet" << endl;
               }
          }
          
          
          else if (command == "setup") {
               if (game == nullptr) {
                    manual_setup = true;
                    game = new Game("human", "human", manual_setup);
                    (*game->getBoardModifiable()).attach(new TextObserver(game->getBoardModifiable()));
                    // (*game->getBoardModifiable()).attach(new GraphicsObserver(game->getBoardModifiable()));
                    string setupCommand;
                    bool whiteKingPlaced = false;
                    bool blackKingPlaced = false;

                    while (cin >> setupCommand) {
                         if (setupCommand == "done") {
                              if (!whiteKingPlaced || !blackKingPlaced) {
                                   cout << "Both kings must be placed on the board." << endl;
                                   continue;
                              }
                              break;
                         }
                         else if (setupCommand == "+") {
                              char piece;
                              string position;
                              cin >> piece >> position;
                              if (!('a' <= position[0] && position[0] <= 'h' && 
                                   '1' <= position[1] && position[1] <= '8')) {
                                   cout << "Invalid coordinate given, try again" << endl;
                                   continue;
                              }
                              if (piece == 'K') {
                              if (whiteKingPlaced) {
                                   cout << "There is already a white king on the board." << endl;
                                   continue;
                                   }
                                   whiteKingPlaced = true;
                              } else if (piece == 'k') {
                                   if (blackKingPlaced) {
                                   cout << "There is already a black king on the board." << endl;
                                   continue;
                                   }
                                   blackKingPlaced = true;
                              }

                              int y = position[1] - '1';

                              if (piece == 'P' && y == 7) {
                                   cout << "Invalid spot for pawn, try again" << endl;
                                   continue;
                              } else if (piece == 'p' && y == 0) {
                                   cout << "Invalid spot for pawn, try again" << endl;
                                   continue;
                              }

                              game->getBoard2().placePiece(piece, position);
                              game->getBoard().display();
                         }

                         else if (setupCommand == "-")
                         {
                              string position;
                              cin >> position;
                              game->getBoard().removePiece(position);
                              game->getBoard().display();
                         }
                         else if (setupCommand == "=")
                         {
                              string colour;
                              cin >> colour;
                              if (colour == "white") {
                                   isWhiteTurn = true;
                              } else if (colour == "black") {
                                   isWhiteTurn = false;
                              } else {
                                   cout << "Enter a valid colour" << endl;
                                   continue;
                              }
                         }
                         else
                         {
                              cout << "Invalid setup command." << endl;
                         }
                    }
               }
               else
               {
                    cout << "Cannot enter setup mode while a game is running." << endl;
               }
          }
          else
          {
               cout << "Unknown command." << endl;
          }
     }

     if (game != nullptr) {
          delete game;
          game = nullptr;
     }
     return 0;
}