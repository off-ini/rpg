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
#include "Outil.h"

using namespace std;

class Personnage : public Creature {
protected:
    int niveauHabilite;
    Sac *sac;
    Outil *outil;

public:
    Personnage();

    Personnage(string nom, int niveauSante, int niveauHabilite);

    Personnage(const Personnage &personnage);

    int getNiveauHabilite();

    void setNiveauHabilite(int niveauHabilite);

    void setSac(Sac *sac);

    Sac *getSac();
    Outil * getOutil();
    void setOutil(int index);
    void setOutil(Outil * outil);

    void attack_i(Personnage * creature);
    void attack(Personnage * creature);

    bool load(int index);
    void updateInfo();

    ~Personnage();

    Personnage &operator=(const Personnage &personnage);

    virtual void print();
    virtual void move(Event& event, TileMap& map);
    virtual void move(TileMap& map);

    Sprite sprite_face;
    Text text_vie;
    Text text_habilite;
    Text text_arme;

protected:
    Texture m_texture_face;
    Font font;
    Clock m_time_anim;
    Clock m_time_moving;
    Clock m_time_direction;
    Clock m_time_attack;
    int m_take_direction = speed;
    bool m_moving = true;

    int getDir(sf::Vector2f pos, sf::Vector2f cible);
    void moving(TileMap& map);
    void moving_cible(TileMap& map);
};


#endif //RPG_PERSONNAGE_H
