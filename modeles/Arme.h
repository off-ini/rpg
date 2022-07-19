//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_ARME_H
#define RPG_ARME_H

#include "Outil.h"

using namespace std;

class Arme : public Outil {
private:
    int point;
    int niveau;

public:
    Arme();

    Arme(string libelle, int point, int niveau);

    int getPoint();

    void setPoint(int point);

    int getNiveau();

    void setNiveau(int niveau);

    void print();

    string toJson();

};


#endif //RPG_ARME_H
