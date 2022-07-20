//
// Created by infini on 20/07/22.
//

#ifndef RPG_BATTLE_H
#define RPG_BATTLE_H

#include "../modeles/Personnage.h"

#include <SFML/Graphics.hpp>

using namespace sf;

class Battle {
public:
    static int battle(RenderWindow& window, Personnage& principale, Personnage* secondaire, int index);
};


#endif //RPG_BATTLE_H
