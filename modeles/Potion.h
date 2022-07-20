//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_POTION_H
#define RPG_POTION_H

#include "Outil.h"

using namespace std;

class Potion : public Outil {

protected:
    int point;

public:
    Potion();

    Potion(string libelle, int point);

    int getPoint();

    void setPoint(int point);

    void print();

    string toJson();

};


#endif //RPG_POTION_H
