//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_RELIGIEUX_H
#define RPG_RELIGIEUX_H

#include "Personnage.h"

using namespace std;

class Religieux : public Personnage {
public:
    Religieux();

    Religieux(string nom, int niveauSante, int niveauHabilite);

    void print();

    string toJson();
};


#endif //RPG_RELIGIEUX_H
