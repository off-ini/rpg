//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_AMULETTE_H
#define RPG_AMULETTE_H

#include "Outil.h"
#include <string>

using namespace std;

class Amulette : public Outil {

private:
    int portee;
    int puissance;

public:
    Amulette();

    Amulette(string libelle, int portee, int puissance);

    virtual int getPortee();

    virtual void setPortee(int portee);

    virtual int getPuissance();

    virtual void setPuissance(int puissance);

    void print();

};


#endif //RPG_AMULETTE_H
