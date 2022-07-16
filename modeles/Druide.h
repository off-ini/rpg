//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_DRUIDE_H
#define RPG_DRUIDE_H

#include "Personnage.h"

using namespace std;

class Druide : public Personnage {
public:
    Druide();

    Druide(string nom, int niveauSante, int niveauHabilite);

    void print();

};


#endif //RPG_DRUIDE_H
