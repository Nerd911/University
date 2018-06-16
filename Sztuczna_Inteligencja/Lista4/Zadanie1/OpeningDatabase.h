//
// Created by nerd911 on 02.05.18.
//

#ifndef ZADANIE1_OPENINGDATABASE_H
#define ZADANIE1_OPENINGDATABASE_H

#include <fstream>
#include "Board.h"
class OpeningDatabase {
public:
    std::unordered_map<std::string, int> openingBook = {};

    OpeningDatabase();
    void loadOpenings();
};


#endif //ZADANIE1_OPENINGDATABASE_H
