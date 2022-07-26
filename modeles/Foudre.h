//
// Created by benjamin on 20/07/22.
//

#ifndef RPG_FOUDRE_H
#define RPG_FOUDRE_H


#include "Amulette.h"

class Foudre : public Amulette {
public:
    Foudre();

    Foudre(string libelle, int portee, int puissance);
};


#endif //RPG_FOUDRE_H
