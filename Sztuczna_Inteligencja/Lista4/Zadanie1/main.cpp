#include <iostream>
#include <cstring>
#include <algorithm>
#include "Game.h"

inline bool simulateGame(float timeLimit, bool bAlphaBeta, bool wAlphaBeta) {
    Game game;
    game.newGame(bAlphaBeta, wAlphaBeta, timeLimit);
    if (game.toMove == -1) {
        game.board.findLegalMoves(-1, &game.board.moves);
        game.move(-1);
        game.checkTerminal();
    }

    while (!game.gameOver) {
        game.board.findLegalMoves(1, &game.board.moves);
        game.move(1);
        game.checkTerminal();

        if (game.gameOver) {
            break;
        }

        game.board.findLegalMoves(-1, &game.board.moves);
        game.move(-1);
        game.checkTerminal();
    }
    int bCntr = (int)std::count(game.board.positions.begin(), game.board.positions.end(), 1);
    int wCntr = (int)std::count(game.board.positions.begin(), game.board.positions.end(), -1);
//    std::cout << bCntr << std::endl;
    return bCntr >= wCntr;
}

int main(int argc, char* argv[]) {
    Board board;
    bool bAlphaBeta = true, wAlphaBeta = false;
    float timeLimit = 0.01;
    if(argc > 1)
        timeLimit = atof(argv[1]);

    int cntr = 0;
    for(int i = 0; i < 1; ++i) {
        if (simulateGame(timeLimit, bAlphaBeta, wAlphaBeta))
            ++cntr;
    }
    std::cout << cntr << std::endl;
    return 0;
}