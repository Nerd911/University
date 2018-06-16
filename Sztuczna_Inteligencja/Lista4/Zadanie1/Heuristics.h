//
// Created by nerd911 on 02.05.18.
//

#ifndef ZADANIE1_HEURISTICS_H
#define ZADANIE1_HEURISTICS_H

#include <numeric>
#include <unordered_set>
#include "Board.h"

class Heuristics {
public:
    int evaluate(Board &board, int player);
private:
    std::unordered_set<int> stableDiscs;
    std::unordered_map<int, std::list<int>> pMoves;

    int utility(Board &board, int &player);
    int discDifference(Board &board, int &player);
    int corners(Board &board, int &player);
    void stableDiscsFromCorner(Board &board, int corner, int player);
    int mobility(Board &board, int &player);
    int stability(Board &board, int player);
    int squareWeights(Board &board, int &player);
};


#endif //ZADANIE1_HEURISTICS_H
