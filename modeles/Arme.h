//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_ARME_H
#define RPG_ARME_H

#include "Outil.h"

using namespace std;

class Arme : public Outil {
protected:
    int point;
    int niveau;

public:
    Arme();

    Arme(string libelle, int point, int niveau);

    virtual  int getPoint();

    virtual void setPoint(int point);

    virtual int getNiveau();

    virtual void setNiveau(int niveau);

    /*virtual int getPortee() { return 0;};

    virtual void setPortee(int portee) {};

    virtual int getPuissance() {return 0;};

    virtual void setPuissance(int puissance) {};*/

    void print();

};


#endif //RPG_ARME_H
