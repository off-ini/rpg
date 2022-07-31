//
// Created by benjamin on 02/07/22.
//
#include <SFML/System.hpp>
#include "../utils/consts.hpp"
#include "../utils/distribution.h"
#include "Personnage.h"
#include "Arme.h"

Personnage::Personnage() : Creature() {
    this->niveauHabilite = 0;
    this->sac = new Sac();//Le sac ne contient pas d'outil
    outil = NULL;
}

Personnage::Personnage(string nom, int niveauSante, int niveauHabilite) : Creature(nom, niveauSante) {
    this->niveauHabilite = niveauHabilite;
    this->sac = new Sac();
    outil = NULL;
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

Outil * Personnage::getOutil(){
    return this->outil;
}

void Personnage::setOutil(int index){
    if(index >= 0 && this->sac->getOutils().size() > index)
        this->outil = this->sac->getOutils()[index];
}

void Personnage::setOutil(Outil * outil){
    this->outil = outil;
}

int Personnage::attack_i(Personnage * creature, int& main, string& corps){

        if(m_time_attack.getElapsedTime().asMilliseconds() >= 5000){
            setOutil(Gen::distNumber(0, sac->getOutils().size() - 1));
            sleep(milliseconds(100));

            int status = attack(creature);
            if(status > -1){
                if(status == 0){
                    main = 1;
                }
                if(outil != NULL)
                    corps += "\n - Enemie -> " + getOutil()->getLibelle() + " #" + to_string(getOutil()->getPoint());
            }

            m_time_attack.restart();
        }

}

int Personnage::attack(Personnage * creature){
    int poid = 7;

    if(outil != NULL){
        if(outil->getLibelle() == "Potion"){
            int niveau = getNiveauSante();
            int point = outil->getPoint();
            if(point >= 5){
                setNiveauSante(niveau + 5);
                outil->setPoint(point - 5);
            }
            else if(point > 0 && point < 5){
                setNiveauSante(niveau + point);
                outil->setPoint(point - point);
            }
            return 1;
        }

        if(outil->getLibelle() == "Cle"){
            int point = outil->getPoint();
            if(point > 0) outil->setPoint(point - 5);
            return 2;
        }

        if(outil->getLibelle() != "Bouclier"){
            if(creature->getOutil() != NULL && creature->getOutil()->getLibelle() == "Bouclier"){
                poid *= poid;
            }
            creature->setNiveauSante( creature->getNiveauSante() - (this->outil->getPoint() * getNiveauHabilite()) / poid);
            return 0;
        }

        return 0;
    }

    return -1;

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

bool Personnage::load(int index){
    if(Creature::loadTexture("./assets/sprites/actors/a"+ to_string(index) +".png")){
        if(!m_texture_face.loadFromFile("./assets/sprites/actors/a_"+ to_string(index) +".png")){
            perror("Texture load error");
            return false;
        }
        m_texture_face.setSmooth(true);

        sprite_face.setTexture(m_texture_face);

        if(!font.loadFromFile("./assets/fonts/teko/Teko-Regular.ttf")){
            perror("'fonTeko' load error");
            return false;
        }

        text_vie.setFont(font);
        text_habilite.setFont(font);
        text_arme.setFont(font);

        text_vie.setFillColor(Color::White);
        text_habilite.setFillColor(Color::White);
        text_arme.setFillColor(Color::White);
    } else return false;

    return true;
}

void Personnage::updateInfo(){
    text_vie.setString(L"Vie :   " + to_string(niveauSante));
    text_habilite.setString(L"Habilité :   " + to_string(niveauHabilite));
    if(outil != NULL)
        text_arme.setString(L"Arme :  " + outil->getLibelle() + " # " + to_string(outil->getPoint()));
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