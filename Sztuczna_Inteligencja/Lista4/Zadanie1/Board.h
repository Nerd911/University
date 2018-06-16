//
// Created by nerd911 on 02.05.18.
//

#ifndef ZADANIE1_BOARD_H
#define ZADANIE1_BOARD_H


#include <unordered_map>
#include <list>
#include <vector>

class Board {
public:
    std::vector<int> positions;
    int discsOnBoard = 4;
    std::unordered_map<int, std::list<int>> moves;
    std::vector<bool> passes;
    float timeLimit = 0.0;
    Board();

    void findLegalMoves(int player, std::unordered_map<int, std::list<int> >* possibleMoves);
    void findLegalMoveInDirection(int &disc, int &player, int dir,
                                  std::unordered_map<int, std::list<int>> *pMoves);

    void updateBoard(int player, std::pair<int, std::list<int>> move);
    bool terminal();
    void index2coord(int index, int &colNum, int &rowNum);


};


#endif //ZADANIE1_BOARD_H
