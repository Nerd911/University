//
// Created by nerd911 on 02.05.18.
//

#ifndef ZADANIE1_GAME_H
#define ZADANIE1_GAME_H


#include "Board.h"
#include "Agent.h"

class Game {
public:
    Board board;
    Agent bPlayer;
    Agent wPlayer;
    std::string moveHistory = "";

    int toMove = 1;
    bool gameOver = false;

    Game();

    void newGame(bool bAlphaBeta, bool wAlphaBeta, float timeLimit);
    void move(int player);
    void checkTerminal();
};


#endif //ZADANIE1_GAME_H
