//
// Created by benjamin on 20/07/22.
//

#ifndef RPG_FEU_H
#define RPG_FEU_H


#include "Amulette.h"

class Feu : public Amulette {

public:
    Feu();

    Feu(string libelle, int portee, int puissance);
};


#endif //RPG_FEU_H
