//
// Created by nerd911 on 02.05.18.
//

#include "OpeningDatabase.h"

OpeningDatabase::OpeningDatabase() {
    loadOpenings();
}

void OpeningDatabase::loadOpenings() {
    std::ifstream csv("../lib/openings.txt");
    std::string pastMoves;
    std::string nextMove;
    int nextMoveInt;

    while (getline(csv, pastMoves)) {
        getline(csv, nextMove);
        nextMoveInt = std::stoi(nextMove);

        //std::cout << pastMoves << std::endl;
        //std::cout << nextMoveInt << std::endl;
        openingBook.insert({pastMoves, nextMoveInt});
    }
}