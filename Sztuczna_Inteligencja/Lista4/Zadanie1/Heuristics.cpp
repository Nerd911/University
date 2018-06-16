//
// Created by nerd911 on 02.05.18.
//

#include "Heuristics.h"
#include <algorithm>

int Heuristics::evaluate(Board &board, int color) {
//    if (board.terminal()) {
        return 100000*utility(board, color);
//    }

    if (board.discsOnBoard <= 20) {
        return 5*mobility(board, color)
               + 20*squareWeights(board, color)
               + 10000*corners(board, color)
               + 10000*stability(board, color);
    }
    else if (board.discsOnBoard <= 58) {
        return 10*discDifference(board, color)
               + 2*mobility(board, color)
               + 10*squareWeights(board, color)
               + 10000*corners(board, color)
               + 10000*stability(board, color);
    }
    else {
        return 500*discDifference(board, color)
               + 10000*corners(board, color)
               + 10000*stability(board, color);
    }
}

int Heuristics::utility(Board &board, int &player) {
    return player * std::accumulate(board.positions.begin(), board.positions.end(), 0);
}

int Heuristics::discDifference(Board &board, int &player) {
    int bCntr = (int)std::count(board.positions.begin(), board.positions.end(), 1);
    int wCntr = (int)std::count(board.positions.begin(), board.positions.end(), -1);

    if (player == 1) {
        return 100 * (bCntr - wCntr) / (bCntr + wCntr);
    }
    else {
        return 100 * (wCntr - bCntr) / (bCntr + wCntr);
    }
}

int Heuristics::mobility(Board &board, int &color) {
    board.findLegalMoves(-1, &pMoves);
    int wMoves = (int)pMoves.size();
    pMoves.clear();

    board.findLegalMoves(1, &pMoves);
    int bMoves = (int)pMoves.size();
    pMoves.clear();
    if (color == 0) {
        return 100 * (wMoves - bMoves) / (bMoves + wMoves + 1);
    }
    else {
        return 100 * (bMoves - wMoves) / (bMoves + wMoves + 1);
    }
}

int Heuristics::stability(Board &board, int player) {
    stableDiscs.clear();
    stableDiscsFromCorner(board, 0, player);
    stableDiscsFromCorner(board, 7, player);
    stableDiscsFromCorner(board, 56, player);
    stableDiscsFromCorner(board, 63, player);

    int playerStables = (int)stableDiscs.size();

    stableDiscsFromCorner(board, 0, -player);
    stableDiscsFromCorner(board, 7, -player);
    stableDiscsFromCorner(board, 56, -player);
    stableDiscsFromCorner(board, 63, -player);

    int opponentStables = (int)stableDiscs.size();

    return playerStables - opponentStables;
}

void Heuristics::stableDiscsFromCorner(Board &board, int corner, int player) {
    int horizontal = (corner % 8 == 0) ? 1 : -1;
    int vertical = (corner < 8) ? 1 : -1;
    int horizIncr = horizontal * 1, horizStop = horizontal * 7, vertIncr = vertical * 8, vertStop = vertical * 56;

    for (int i = corner; i != corner + horizIncr + horizStop; i += horizIncr) {
        if (board.positions[i] == player) {
            for (int j = i; j != i + vertStop; j+= vertIncr) {
                if (board.positions[j] == player
                    && stableDiscs.find(j) == stableDiscs.end()) {
                    stableDiscs.insert(j);
                }
                else {
                    break;
                }
            }
        }
        else {
            break;
        }
    }
}

int Heuristics::squareWeights(Board &board, int &player) {
    std::vector<int> weights = {
            200, -100, 100,  50,  50, 100, -100,  200,
            -100, -200, -50, -50, -50, -50, -200, -100,
            100,  -50, 100,   0,   0, 100,  -50,  100,
            50,  -50,   0,   0,   0,   0,  -50,   50,
            50,  -50,   0,   0,   0,   0,  -50,   50,
            100,  -50, 100,   0,   0, 100,  -50,  100,
            -100, -200, -50, -50, -50, -50, -200, -100,
            200, -100, 100,  50,  50, 100, -100,  200,
    };

    if (board.positions[0]) {
        weights[1]  = 0;
        weights[2]  = 0;
        weights[3]  = 0;
        weights[8]  = 0;
        weights[9]  = 0;
        weights[10] = 0;
        weights[11] = 0;
        weights[16] = 0;
        weights[17] = 0;
        weights[18] = 0;
        weights[24] = 0;
        weights[25] = 0;
    }

    if (board.positions[7]) {
        weights[4]  = 0;
        weights[5]  = 0;
        weights[6]  = 0;
        weights[12] = 0;
        weights[13] = 0;
        weights[14] = 0;
        weights[15] = 0;
        weights[21] = 0;
        weights[22] = 0;
        weights[23] = 0;
        weights[30] = 0;
        weights[31] = 0;
    }

    if (board.positions[56]) {
        weights[32] = 0;
        weights[33] = 0;
        weights[40] = 0;
        weights[41] = 0;
        weights[42] = 0;
        weights[48] = 0;
        weights[49] = 0;
        weights[50] = 0;
        weights[51] = 0;
        weights[57] = 0;
        weights[58] = 0;
        weights[59] = 0;
    }

    if (board.positions[63]) {
        weights[38] = 0;
        weights[39] = 0;
        weights[45] = 0;
        weights[46] = 0;
        weights[47] = 0;
        weights[52] = 0;
        weights[53] = 0;
        weights[54] = 0;
        weights[55] = 0;
        weights[60] = 0;
        weights[61] = 0;
        weights[62] = 0;
    }

    if (player == 1)
        return std::inner_product(board.positions.begin(), board.positions.end(), weights.begin(), 0);
    else
        return -1*std::inner_product(board.positions.begin(), board.positions.end(), weights.begin(), 0);

}


int Heuristics::corners(Board &board, int &player) {
    std::vector<int> corners = {0, 7, 56, 63};
    int bCorners = 0;
    int wCorners = 0;

    for (int corner : corners) {
        if (board.positions[corner] == 1) {
            bCorners++;
        }
        else if (board.positions[corner] == -1) {
            wCorners++;
        }
    }

    if (player == 1) {
        return 100 * (bCorners - wCorners)
               / (bCorners + wCorners + 1);
    }
    else {
        return 100 * (wCorners - bCorners)
               / (bCorners + wCorners + 1);
    }
}