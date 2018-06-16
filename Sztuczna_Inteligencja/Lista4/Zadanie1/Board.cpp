//
// Created by nerd911 on 02.05.18.
//

#include "Board.h"

Board::Board() {
    positions = std::vector<int>(64, 0);
    passes = std::vector<bool>(2, false);
}

void Board::findLegalMoves(int player, std::unordered_map<int, std::list<int>> *pMoves) {
    this->moves.clear();

    for (int i = 0; i < 64; i++) {
        if (this->positions[i] == player) {
            findLegalMoveInDirection(i, player, -1, pMoves);
            findLegalMoveInDirection(i, player, 1, pMoves);
            findLegalMoveInDirection(i, player, -8, pMoves);
            findLegalMoveInDirection(i, player, 8, pMoves);
            findLegalMoveInDirection(i, player, -9, pMoves);
            findLegalMoveInDirection(i, player, 9, pMoves);
            findLegalMoveInDirection(i, player, -7, pMoves);
            findLegalMoveInDirection(i, player, 7, pMoves);
        }
    }


}

void Board::findLegalMoveInDirection(int &disc, int &player, int dir, std::unordered_map<int, std::list<int>> *pMoves) {
    std::pair<int, std::list<int>> legalMove;
    std::list<int> flippedDiscs;
    int currentSquare = 0;
    int row1 = 0, col1 = 0, row2 = 0, col2 = 0;

    for (int i = disc + dir; i < 64 && i > -1; i += dir) {
        index2coord(i-dir, col1, row1);
        index2coord(i, col2, row2);
        if (abs(col1 - col2) > 1 || abs(row1 - row2) > 1) {
            break;
        }
        currentSquare = this->positions[i];
        if (currentSquare == player ||
            (currentSquare == 0 && flippedDiscs.empty())) {
            break;
        }
        else if (currentSquare == -player) {
            flippedDiscs.push_front(i);
            continue;
        }

        else if (currentSquare == 0 && !flippedDiscs.empty()) {
            std::unordered_map<int, std::list<int>>::iterator it = pMoves->find(i);

            if (it != pMoves->end()) {
                it->second.merge(flippedDiscs);
            }
            else {
                legalMove.first = i;
                legalMove.second = flippedDiscs;
                pMoves->insert(legalMove);
            }

            break;
        }
    }
}

void Board::updateBoard(int player, std::pair<int, std::list<int>> move) {
    int square = move.first;
    std::list<int> flippedDiscs = move.second;

    this->positions[square] = player;
    for (auto disc : flippedDiscs) {
        this->positions[disc] = player;
    }
}

bool Board::terminal() {
    if (this->passes[0] && this->passes[1]) {
        return true;
    }
    return false;
}


void Board::index2coord(int index, int &colNum, int &rowNum) {
    colNum = index % 8;
    rowNum = index / 8;
}