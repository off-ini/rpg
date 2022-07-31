//
// Created by infini on 19/07/22.
//

#ifndef RPG_CHOIXPERSO_H
#define RPG_CHOIXPERSO_H

#include "../utils/consts.hpp"

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class PersoSelect{
public:
    RectangleShape rectangle;

    Texture textureMini;
    Texture textureFace;

    Sprite spriteMini;
    Sprite spriteFace;

    std::string type;

    void load(int i);
    void setPosition(float x, float y);
    bool onMouseEnter(RenderWindow& window);
};

class ChoixPerso {
public:
    static int choix(RenderWindow& window);
};


#endif //RPG_CHOIXPERSO_H
