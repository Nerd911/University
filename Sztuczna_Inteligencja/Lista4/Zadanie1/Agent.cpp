//
// Created by nerd911 on 02.05.18.
//

#include "Agent.h"

std::pair<int, std::list<int>> Agent::move(Board &board, std::unordered_map<int, std::list<int>> &legalMoves, bool &pass, std::string &moveHistory) {

    std::pair<int, std::list<int>> moveChoice;
    if (alphaBeta)
        moveChoice = alphaBetaMove(board, legalMoves, pass, moveHistory);
    else
        moveChoice = randomMove(board, legalMoves, pass);

    moveHistory.append(std::to_string(moveChoice.first) + ",");

    return moveChoice;
}

std::pair<int, std::list<int>> Agent::alphaBetaMove(Board &board, std::unordered_map<int, std::list<int>> &legalMoves,
                                                    bool &pass, std::string &moveHistory){
    std::chrono::time_point<std::chrono::system_clock> startTime
            = startTimer();
    std::pair<int, std::list<int>> move;
    std::pair<int, std::list<int>> bestMove;
    std::unordered_map<std::string, int>::iterator query
            = database.openingBook.find(moveHistory);

    if (legalMoves.empty()) {
        pass = true;
        return bestMove;
    }
    else if (legalMoves.size() == 1) {
        bestMove = *legalMoves.begin();
    }
    else if (query != database.openingBook.end()) {
        bestMove = *legalMoves.find(query->second);
    }
    else {
        int maxDepth = 64 - board.discsOnBoard;

        if (maxDepth < 10) {
            bestMove = depthLimitedAlphaBeta(board, maxDepth, startTime,
                                                   board.timeLimit);
        }
        else {
            for (int depthLimit = 1; depthLimit <= maxDepth; depthLimit++) {
                move = depthLimitedAlphaBeta(board, depthLimit, startTime,
                                                   board.timeLimit);

                if (move.first == -1) {
                    break;
                }
                else {
                    bestMove = move;
                }

                if (stopTimer(startTime) > 0.5*board.timeLimit) {
                    break;
                }
            }
        }
    }
    return bestMove;
}

std::chrono::time_point<std::chrono::system_clock> Agent::startTimer() {
    return std::chrono::system_clock::now();
}

float Agent::stopTimer(
        std::chrono::time_point<std::chrono::system_clock> startTime) {
    std::chrono::time_point<std::chrono::system_clock> endTime =
            std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedSeconds = endTime - startTime;
    return elapsedSeconds.count();
}

std::pair<int, std::list<int>> Agent::depthLimitedAlphaBeta(
        Board &board, int depthLimit,
        std::chrono::time_point<std::chrono::system_clock> startTime,
        float timeLimit) {
    nodeStack[0].isMaxNode = true;
    nodeStack[0].alpha = INT_MIN;
    nodeStack[0].beta = INT_MAX;
    nodeStack[0].score = INT_MIN;
    nodeStack[0].board = board;
    nodeStack[0].moveIterator = nodeStack[0].board.moves.begin();
    nodeStack[0].prevIterator = nodeStack[0].moveIterator;
    nodeStack[0].lastMove = nodeStack[0].board.moves.end();

    int depth = 0;
    int leafScore = 0;
    std::unordered_map<int, std::list<int>>::iterator bestMove =
            nodeStack[0].board.moves.begin();

    // While we have not evaluated all the root's children
    while (true) {
        // If we have evaluated all children
        if (nodeStack[depth].moveIterator == nodeStack[depth].lastMove) {
            if (depth-- == 0) {
                if (nodeStack[1].score > nodeStack[0].score
                    || (nodeStack[1].score == nodeStack[0].score
                        && rand() % 2 == 0)) {
                    nodeStack[0].score = nodeStack[1].score;
                    bestMove = nodeStack[0].prevIterator;
                }

                if (nodeStack[0].score > nodeStack[0].alpha) {
                    nodeStack[0].alpha = nodeStack[0].score;
                }

                break;
            }

            if (nodeStack[depth].isMaxNode) {
                if (nodeStack[depth+1].score > nodeStack[depth].score
                    || (nodeStack[depth+1].score == nodeStack[depth].score
                        && rand() % 2 == 0)) {
                    nodeStack[depth].score = nodeStack[depth+1].score;
                    if (depth == 0) {
                        bestMove = nodeStack[0].prevIterator;
                    }
                }

                if (nodeStack[depth].score > nodeStack[depth].alpha) {
                    nodeStack[depth].alpha = nodeStack[depth].score;
                }
            }
            else {
                if (nodeStack[depth+1].score < nodeStack[depth].score) {
                    nodeStack[depth].score = nodeStack[depth+1].score;
                }

                if (nodeStack[depth].score < nodeStack[depth].beta) {
                    nodeStack[depth].beta = nodeStack[depth].score;
                }
            }
        }
            // If we can prune
        else if (nodeStack[depth].beta <= nodeStack[depth].alpha) {
            if (depth-- == 0) {
                if (nodeStack[1].score > nodeStack[0].score
                    || (nodeStack[1].score == nodeStack[0].score
                        && rand() % 2 == 0)) {
                    nodeStack[0].score = nodeStack[1].score;
                    bestMove = nodeStack[0].prevIterator;
                }

                if (nodeStack[0].score > nodeStack[0].alpha) {
                    nodeStack[0].alpha = nodeStack[0].score;
                }
                break;
            }

            if (nodeStack[depth].isMaxNode) {
                if (nodeStack[depth+1].score > nodeStack[depth].score
                    || (nodeStack[depth+1].score == nodeStack[depth].score
                        && rand() % 2 == 0)) {
                    nodeStack[depth].score = nodeStack[depth+1].score - 1;
                    if (depth == 0) {
                        bestMove = nodeStack[0].prevIterator;
                    }
                }

                if (nodeStack[depth].score > nodeStack[depth].alpha) {
                    nodeStack[depth].alpha = nodeStack[depth].score;
                }
            }
            else {
                if (nodeStack[depth+1].score < nodeStack[depth].score) {
                    nodeStack[depth].score = nodeStack[depth+1].score + 1;
                }

                if (nodeStack[depth].score < nodeStack[depth].beta) {
                    nodeStack[depth].beta = nodeStack[depth].score;
                }
            }
        }
        else {
            // Generate next node, increment iterators
            nodeStack[depth+1].board = nodeStack[depth].board;
            nodeStack[depth+1].board.updateBoard(
                    (nodeStack[depth].isMaxNode ? playerColor : -playerColor),
                    *nodeStack[depth].moveIterator);
            nodeStack[depth].prevIterator = nodeStack[depth].moveIterator;
            nodeStack[depth].moveIterator++;

            // If the next depth is not at the depth limit
            if (depth + 1 < depthLimit) {
                depth++;

                // Initialize next node in stack
                nodeStack[depth].isMaxNode = !nodeStack[depth-1].isMaxNode;
                nodeStack[depth].score =
                        (nodeStack[depth].isMaxNode ? INT_MIN : INT_MAX);
                nodeStack[depth].alpha = nodeStack[depth-1].alpha;
                nodeStack[depth].beta = nodeStack[depth-1].beta;
                nodeStack[depth].board.findLegalMoves(
                        (nodeStack[depth].isMaxNode ? playerColor : -playerColor),
                        &nodeStack[depth].board.moves);

                nodeStack[depth].moveIterator =
                        nodeStack[depth].board.moves.begin();
                nodeStack[depth].prevIterator =
                        nodeStack[depth].moveIterator;
                nodeStack[depth].lastMove = nodeStack[depth].board.moves.end();
            }
            else {
                // The node is a leaf: evaluate heuristic and update values
                leafScore = heuristics.evaluate(
                        nodeStack[depth+1].board, playerColor);

                if (nodeStack[depth].isMaxNode) {
                    if (leafScore > nodeStack[depth].score) {
                        nodeStack[depth].score = leafScore;
                        if (depth == 0) {
                            bestMove = nodeStack[0].prevIterator;
                        }
                    }

                    if (nodeStack[depth].score > nodeStack[depth].alpha) {
                        nodeStack[depth].alpha = nodeStack[depth].score;
                    }
                }
                else {
                    if (leafScore < nodeStack[depth].score) {
                        nodeStack[depth].score = leafScore;
                    }

                    if (nodeStack[depth].score < nodeStack[depth].beta) {
                        nodeStack[depth].beta = nodeStack[depth].score;
                    }
                }
            }
        }

        // If we are almost out of time, failure
        if (stopTimer(startTime) > 0.998*timeLimit) {
            std::pair<int, std::list<int>> move;
            move.first = -1;
            return move;
        }
    }

    return *bestMove;
}

int rand_between(int b, int e) {
    srand(time(NULL));
    return (rand() % (b-e)) + b;
}

std::pair<int, std::list<int>>
Agent::randomMove(Board &board, std::unordered_map<int, std::list<int>> &legalMoves, bool &pass) {
    std::pair<int, std::list<int>> move;
    if (legalMoves.empty()) {
        pass = true;
        return move;
    }
    auto random_it = std::next(std::begin(legalMoves), rand_between(0, (int)legalMoves.size()));
    move = *random_it;
    return move;
}
