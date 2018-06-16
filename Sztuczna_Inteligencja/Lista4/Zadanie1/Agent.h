//
// Created by nerd911 on 02.05.18.
//

#ifndef ZADANIE1_AGENT_H
#define ZADANIE1_AGENT_H

#include <string>
#include <array>
#include <chrono>
#include <climits>
#include <iterator>
#include <sstream>
#include "Heuristics.h"
#include "OpeningDatabase.h"

class Agent {
public:
    int playerColor;
    bool alphaBeta;

    std::pair<int, std::list<int>> move(Board &board, std::unordered_map<int, std::list<int>> &legalMoves, bool &pass, std::string &moveHistory);
private:
    struct SearchNode {
        bool isMaxNode;
        int alpha;
        int beta;
        int score;
        Board board;
        std::unordered_map<int, std::list<int>>::iterator prevIterator;
        std::unordered_map<int, std::list<int>>::iterator moveIterator;
        std::unordered_map<int, std::list<int>>::iterator lastMove;
    };

    std::array<SearchNode, 64> nodeStack = {};
    Heuristics heuristics;
    OpeningDatabase database;

    std::pair<int, std::list<int>> randomMove(Board &board, std::unordered_map<int, std::list<int>> &legalMoves, bool &pass);

    std::pair<int, std::list<int>> alphaBetaMove(Board &board,
                                                 std::unordered_map<int, std::list<int>> &legalMoves, bool &pass, std::string &moveHistory);

    std::chrono::time_point<std::chrono::system_clock> startTimer();
    float stopTimer(std::chrono::time_point<std::chrono::system_clock> startTime);
    std::pair<int, std::list<int>> depthLimitedAlphaBeta(
            Board &theBoard, int depthLimit,
            std::chrono::time_point<std::chrono::system_clock> startTime,
            float timeLimit);
};


#endif //ZADANIE1_AGENT_H
