//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_OUVRIER_H
#define RPG_OUVRIER_H

#include "Personnage.h"

using namespace std;

class Ouvrier : public Personnage {
public:
    Ouvrier();

    Ouvrier(string nom, int niveauSante, int niveauHabilite);

    void print();

    string toJson();

};


#endif //RPG_OUVRIER_H
