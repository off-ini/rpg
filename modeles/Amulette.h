//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_AMULETTE_H
#define RPG_AMULETTE_H

#include "Outil.h"
#include <string>

using namespace std;

class Amulette : public Outil {

protected:
    int portee;
    int puissance;

public:
    Amulette();

    Amulette(string libelle, int portee, int puissance);

    int getPortee();

    void setPortee(int portee);

    int getPuissance();

    void setPuissance(int puissance);

    void print();

    string toJson();

};


#endif //RPG_AMULETTE_H
