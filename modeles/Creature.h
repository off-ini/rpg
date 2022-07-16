//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_CREATURE_H
#define RPG_CREATURE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "../utils/consts.hpp"
#include "../utils/tilemap.hpp"
#include "GameObject.h"

#define CIBLE_DISTANCE 100
#define DIRECTION_RAND_MAX 3
#define SPEED 5

using namespace std;
using namespace sf;

class Creature : public GameObject {
protected:
    string nom;
    int niveauSante;

    Creature* cible;

    float speed;
    enum Dir{Down, Left, Right, Up};
    Vector2i anim;
    bool updateAnim = true;

    Texture texture;

public:
    Sprite sprite;
    Creature();

    Creature(string nom, int niveauSante);

    string getNom();

    void setNom(string nom);

    int getNiveauSante();

    void setNiveauSante(int niveauSante);

    bool loadTexture(const string& path);
    Texture getTexture();

    float getSpeed();
    void setSpeed(float speed_value);
    void setPosition(float& x, float& y);
    void setPosition(Vector2f& pos);
    const Vector2f& getPosition();

    Creature* getCible();
    double cibleDisctance(Creature& cibler);
    void setCible(Creature& cibler);
    void setCible(std::vector<Creature *> cible);
    bool hasCible();

    virtual void print();
    virtual void move(Event& event, TileMap& map) = 0;
    virtual void move(TileMap& map) = 0;

};


#endif //RPG_CREATURE_H
