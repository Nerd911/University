//
// Created by nerd911 on 02.05.18.
//

#include <algorithm>
#include <iostream>
#include "Game.h"

Game::Game() {
    this->board.positions.resize(64, 0);
}

void Game::newGame(bool blackAlphaBeta, bool whiteAlphaBeta,
                          float timeLimit) {
    // Initialize board


    std::fill(this->board.positions.begin(), this->board.positions.end(), 0);


    this->board.positions[27] = -1;
    this->board.positions[28] = 1;
    this->board.positions[35] = 1;
    this->board.positions[36] = -1;

    this->bPlayer.playerColor = 1;
    this->bPlayer.alphaBeta = blackAlphaBeta;
    this->wPlayer.playerColor = -1;
    this->wPlayer.alphaBeta = whiteAlphaBeta;

    this->toMove = 1;

    // Initialize time limit
    this->board.timeLimit = timeLimit;
}

// Make a move
void Game::move(int player) {
    std::pair<int, std::list<int>> move;

    if (player == 1) {
        move = this->bPlayer.move(this->board, this->board.moves,
                                      this->board.passes[0], this->moveHistory);
    }
    else if (player == -1) {
        move = this->wPlayer.move(this->board, this->board.moves,
                                      this->board.passes[0], this->moveHistory);
    }

    if (!this->board.passes[0]) {
        this->board.updateBoard(player, move);
    }
}

// Update status of the game
void Game::checkTerminal(){
    if (this->board.passes[0] && this->board.passes[1]) {
        this->gameOver = true;
    }
    else {
        if (!this->board.passes[0]) {
            this->board.discsOnBoard++;
        }

        this->board.passes[1] = this->board.passes[0];
        this->board.passes[0] = false;
    }
}