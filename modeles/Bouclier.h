//
// Created by infini on 20/07/22.
//

#ifndef RPG_BOUCLIER_H
#define RPG_BOUCLIER_H

#include "Arme.h"

class Bouclier : public Arme{
public:
    Bouclier();
    Bouclier(string libelle, int point, int niveau);
};


#endif //RPG_BOUCLIER_H
