//
// Created by benjamin on 20/07/22.
//

#ifndef RPG_POTIONREGENERATION_H
#define RPG_POTIONREGENERATION_H


#include "Potion.h"

class PotionRegeneration: public Potion {
public:
    PotionRegeneration();
    PotionRegeneration(int point);

    PotionRegeneration(string libelle, int point);
};


#endif //RPG_POTIONREGENERATION_H
