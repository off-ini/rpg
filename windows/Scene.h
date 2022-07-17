//
// Created by infini on 15/07/22.
//

#ifndef RPG_SCENE_H
#define RPG_SCENE_H

#include "../modeles/Personnage.h"
#include "../modeles/Batiment.h"
#include "../modeles/Piece.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define PERSO_NOMBRE 60

class Scene {
public:
    Scene();
    int scene1(sf::RenderWindow& window);
private:
    View view;
    Batiment batiment;
    vector<Piece *> pieces;

    void setView(Personnage * personnage);
    void createLevel1();
    sf::Vector2f randomPosition();
};


#endif //RPG_SCENE_H
