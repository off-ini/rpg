//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_PERSONNAGE_H
#define RPG_PERSONNAGE_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "Creature.h"
#include "Sac.h"

using namespace std;

class Personnage : public Creature {
private:
    Clock m_time_anim;
    Clock m_time_moving;
    Clock m_time_direction;
    int m_take_direction = speed;
    bool m_moving = true;

    int getDir(sf::Vector2f pos, sf::Vector2f cible);

    void moving(TileMap &map);

    void moving_cible(TileMap &map);

protected:
    int niveauHabilite;
    Sac *sac;

public:
    Personnage();

    Personnage(string nom, int niveauSante, int niveauHabilite);

    Personnage(const Personnage &personnage);

    int getNiveauHabilite();

    void setNiveauHabilite(int niveauHabilite);

    void setSac(Sac *sac);

    Sac *getSac();

    ~Personnage();

    Personnage &operator=(const Personnage &personnage);

    virtual void print();

    virtual string toJson();

    virtual void move(Event &event, TileMap &map);

    virtual void move(TileMap &map);

};


#endif //RPG_PERSONNAGE_H
