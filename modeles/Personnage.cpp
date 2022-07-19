//
// Created by benjamin on 02/07/22.
//
#include "../utils/consts.hpp"
#include "../utils/distribution.h"
#include "Personnage.h"

Personnage::Personnage() : Creature() {
    this->niveauHabilite = 0;
    this->sac = new Sac();//Le sac ne contient pas d'outil
}

Personnage::Personnage(string nom, int niveauSante, int niveauHabilite) : Creature(nom, niveauSante) {
    this->niveauHabilite = niveauHabilite;
    this->sac = new Sac();
}

Personnage::Personnage(const Personnage &personnage) {
    this->nom = nom;
    this->niveauSante = niveauSante;
    this->niveauHabilite = niveauHabilite;

    //Suppression d'éventuels outils dans le sac de la personne
    if (this->sac) {
        delete this->sac;
    }

    //Copie du sac
    this->sac = new Sac();
    this->sac = personnage.sac;//appel de la redéfinition de l'opérateur d'affectation dans sac
}

int Personnage::getNiveauHabilite() {
    return this->niveauHabilite;
}

void Personnage::setNiveauHabilite(int niveauHabilite) {
    this->niveauHabilite = niveauHabilite;
}

void Personnage::setSac(Sac *sac) {
    if (this->sac) {
        delete this->sac;
    }
    this->sac = sac;
}

Sac *Personnage::getSac() {
    return this->sac;
}

Personnage::~Personnage() {
    if (this->sac) {
        delete this->sac;
    }
}

Personnage &Personnage::operator=(const Personnage &personnage) {
    this->nom = nom;
    this->niveauSante = niveauSante;
    this->niveauHabilite = niveauHabilite;

    //Suppression d'éventuel outils dans le sac de la personne
    if (this->sac) {
        delete this->sac;//destructeur de sac appelé
    }

    //Copie du sac
    this->sac = new Sac();
    this->sac = personnage.sac;//redéfinition de l'opérateur d'affectation dans sac

    return *this;
}

void Personnage::print() {
    string ecran;
    ecran = "Personnage[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante)
            + ", niveauHabilete:  " + to_string(this->niveauHabilite) + ", ";
    cout << endl << ecran << "\t";
    this->sac->print();
    cout << "]" << endl;
}

string Personnage::toJson() {
    string type = &(typeid(*this).name()[1]);
    string json;
    json = "{\"type\": \"" + type + "\", \"nom\": \"" + this->nom + "\", \"niveauSante\": " +
           to_string(this->niveauSante)
           + ", \"niveauHabilete\": " + to_string(this->niveauHabilite) + ", \"sac\": [";
    json += this->sac->toJson();
    json += "]}";
    return json;
}

void Personnage::move(Event &event, TileMap &map) {
    if (event.type == Event::KeyPressed) updateAnim = true;
    else updateAnim = false;

    if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) {
        if (!map.isTileWall(sprite.getPosition(), Down, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
            sprite.move(0, speed);
        }
        anim.y = Down;
    } else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Q)) {
        if (!map.isTileWall(sprite.getPosition(), Left, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
            sprite.move(-speed, 0);
        }
        anim.y = Left;
    } else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
        if (!map.isTileWall(sprite.getPosition(), Right, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
            sprite.move(speed, 0);
        }
        anim.y = Right;
    } else if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Z)) {
        if (!map.isTileWall(sprite.getPosition(), Up, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
            sprite.move(0, -speed);
        }
        anim.y = Up;
    }

    if (updateAnim) {
        if (m_time_anim.getElapsedTime().asMilliseconds() >= (int) (speed * 20)) {
            anim.x++;
            if (anim.x * PERSO_WIDTH >= texture.getSize().x)
                anim.x = 0;
            m_time_anim.restart();
        }
    }
    sprite.setTextureRect(IntRect(anim.x * PERSO_WIDTH, anim.y * PERSO_HEIGHT, PERSO_WIDTH, PERSO_HEIGHT));
}

void Personnage::move(TileMap &map) {

    if (hasCible()) {
        moving_cible(map);
    } else {
        moving(map);
    }

    sprite.setTextureRect(IntRect(anim.x * PERSO_WIDTH, anim.y * PERSO_HEIGHT, PERSO_WIDTH, PERSO_HEIGHT));
}

int Personnage::getDir(sf::Vector2f pos, sf::Vector2f cible) {
    int directionX = 0;
    int directionY = 0;
    if (cible.x < pos.x) {
        directionX = Left;
    } else {
        directionX = Right;
    }

    if (cible.y < pos.y) {
        directionY = Up;
    } else {
        directionY = Down;
    }

    if (std::pow(pos.x - cible.x, 2) < std::pow(pos.y - cible.y, 2))
        return directionY;
    else return directionX;
}

void Personnage::moving(TileMap &map) {
    if (m_time_moving.getElapsedTime().asMilliseconds() >= (int) (speed * 20)) {
        if (m_time_direction.getElapsedTime().asSeconds() >= m_take_direction) {
            anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
            m_take_direction = Gen::distNumber(speed, speed * 4);
            m_time_direction.restart();
        }

        if (anim.y == Down) {
            updateAnim = true;
            if (!map.isTileWall(sprite.getPosition(), Down, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
                sprite.move(0, speed);
            } else {
                updateAnim = false;
                anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
            }

        } else if (anim.y == Left) {
            updateAnim = true;
            if (!map.isTileWall(sprite.getPosition(), Left, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
                sprite.move(-speed, 0);
            } else {
                updateAnim = false;
                anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
            }
        } else if (anim.y == Right) {
            updateAnim = true;
            if (!map.isTileWall(sprite.getPosition(), Right, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
                sprite.move(speed, 0);
            } else {
                updateAnim = false;
                anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
            }
        } else if (anim.y == Up) {
            updateAnim = true;
            if (!map.isTileWall(sprite.getPosition(), Up, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
                sprite.move(0, -speed);
            } else {
                updateAnim = false;
                anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
            }
        }

        if (updateAnim) {
            if (m_time_anim.getElapsedTime().asMilliseconds() >= (int) (speed * 6)) {
                anim.x++;
                if (anim.x * PERSO_WIDTH >= texture.getSize().x)
                    anim.x = 0;
                m_time_anim.restart();
            }
        }
        m_time_moving.restart();
    }
}

void Personnage::moving_cible(TileMap &map) {
    sf::Vector2f cibler_pos(cible->sprite.getPosition().x + (PERSO_WIDTH / 2),
                            cible->sprite.getPosition().y + (PERSO_HEIGHT / 2));
    sf::Vector2f pos(sprite.getPosition().x + (PERSO_WIDTH / 2), sprite.getPosition().y + (PERSO_HEIGHT / 2));

    int dir = getDir(pos, cibler_pos);
    if (((dir == 0 || dir == 3) && cibleDisctance(*cible) <= PERSO_WIDTH + speed) ||
        ((dir == 1 || dir == 2) && cibleDisctance(*cible) <= PERSO_HEIGHT + speed)) {
        m_moving = false;
    } else {
        m_moving = true;
    }

    if (m_time_moving.getElapsedTime().asMilliseconds() >= (int) (speed * 20) && m_moving) {

        if (m_time_direction.getElapsedTime().asSeconds() >= 1) {
            anim.y = dir;
            m_time_direction.restart();
        }

        if (anim.y == Down) {
            updateAnim = true;
            if (!map.isTileWall(sprite.getPosition(), Down, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
                sprite.move(0, speed);
            } else {
                updateAnim = false;
                anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
            }

        } else if (anim.y == Left) {
            updateAnim = true;
            if (!map.isTileWall(sprite.getPosition(), Left, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
                sprite.move(-speed, 0);
            } else {
                updateAnim = false;
                anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
            }
        } else if (anim.y == Right) {
            updateAnim = true;
            if (!map.isTileWall(sprite.getPosition(), Right, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
                sprite.move(speed, 0);
            } else {
                updateAnim = false;
                anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
            }
        } else if (anim.y == Up) {
            updateAnim = true;
            if (!map.isTileWall(sprite.getPosition(), Up, PERSO_WIDTH, PERSO_HEIGHT, speed)) {
                sprite.move(0, -speed);
            } else {
                updateAnim = false;
                anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
            }
        }

        if (updateAnim) {
            if (m_time_anim.getElapsedTime().asMilliseconds() >= (int) (speed * 6)) {
                anim.x++;
                if (anim.x * PERSO_WIDTH >= texture.getSize().x)
                    anim.x = 0;
                m_time_anim.restart();
            }
        }
        m_time_moving.restart();
    }
}