#include <iostream>
#include <string>

#include "../include/game.h"
#include "board.h"
#include "player.h"
#include "move.h"
#include "../include/square.h"

#include "textObserver.h"

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
               cout << "New game started between " << p1 << " and " << p2 << "." << endl;
               new_game_started = true;
               cout << "It is white's turn" << endl;
               game->getBoard().display();
          }
          
          
          // else if (command == "resign") {
          //      if (game != nullptr && !game->isGameOver()) {
          //           if (game->isWhiteTurn()) {
          //                cout << "White resigns. Black wins!" << endl;
          //           } else {
          //                cout << "Black resigns. White wins!" << endl;
          //           }
          //           delete game;
          //           game = nullptr;
          //      } else {
          //           cout << "No game is currently running." << endl;
          //      }
          // }
          
          
          else if (command == "move") {
               if (game != nullptr) {
                    Player* currentPlayer = game->getCurrentPlayer();
                    
                    if (currentPlayer->getType() == PlayerType::HUMAN) {
                         if (!currentPlayer->makeMove(game, game->getBoard2(), isWhiteTurn)) {
                              continue;
                         } else {
                              game->changeTurns();
                              isWhiteTurn = !isWhiteTurn;
                         }
                    } else if (currentPlayer->getType() == PlayerType::COMPUTER1) {
                         if (!currentPlayer->makeMove(game, game->getBoard2(), isWhiteTurn)) {
                              continue;
                         } else {
                              game->changeTurns();
                              isWhiteTurn = !isWhiteTurn;
                         }
                    }
                    cout << "It is " << (isWhiteTurn ? "white's" : "black's") << " turn" << endl;
                    game->getBoard().display();
               }
               else
               {
                    cout << "No game is currently running." << endl;
               }
          } else if (command == "render") {
               if (game != nullptr) {
                    game->getBoard().display();
               }
          }
          
          
          else if (command == "setup") {
               if (game == nullptr) {
                    manual_setup = true;
                    game = new Game("human", "human", manual_setup);
                    (*game->getBoardModifiable()).attach(new TextObserver(game->getBoardModifiable()));
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

                              game->getBoard().placePiece(piece, position);
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
     }

     return 0;
}