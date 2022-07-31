//
// Created by benjamin on 02/07/22.
//
#include "Creature.h"
#include "../utils/distribution.h"

Creature::Creature() : nom(""), niveauSante(0) {
    anim.x = 0;
    anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
    speed = SPEED;
    cible = NULL;
}

Creature::Creature(string nom, int niveauSante) {
    this->nom = nom;
    this->niveauSante = niveauSante;

    anim.x = 0;
    anim.y = Gen::distNumber(0, DIRECTION_RAND_MAX);
    speed = SPEED;
    cible = NULL;
}

string Creature::getNom() {
    return this->nom;
}

void Creature::setNom(string nom) {
    this->nom = nom;
}

int Creature::getNiveauSante() {
    if(this->niveauSante <= 0) this->niveauSante = 0;
    return this->niveauSante;
}

void Creature::setNiveauSante(int niveauSante) {
    this->niveauSante = niveauSante;
}

bool Creature::loadTexture(const string& path){
    if(!texture.loadFromFile(path)){
        perror("Texture load error");
        return false;
    }
    texture.setSmooth(true);

    sprite.setTexture(texture);
    return true;
}
Texture Creature::getTexture(){
    return texture;
}

float Creature::getSpeed(){
    return speed;
}
void Creature::setSpeed(float speed_value){
    speed = speed_value;
}

void Creature::setPosition(float& x, float& y){
    sprite.setPosition(x, y);
}
void Creature::setPosition(Vector2f& pos){
    sprite.setPosition(pos);
}
const Vector2f& Creature::getPosition(){
    return sprite.getPosition();
}

Creature* Creature::getCible(){
    return cible;
}

double Creature::cibleDisctance(Creature& cibler){
    sf::Vector2f cibler_pos(cibler.sprite.getPosition().x + (PERSO_WIDTH/2), cibler.sprite.getPosition().y + (PERSO_HEIGHT/2));
    sf::Vector2f pos(sprite.getPosition().x + (PERSO_WIDTH/2), sprite.getPosition().y + (PERSO_HEIGHT/2));

    return std::sqrt(std::pow((cibler_pos.x - pos.x),2) + std::pow((cibler_pos.y - pos.y),2));
}

void Creature::setCible(Creature& cibler){
    if(cibleDisctance(cibler) <= CIBLE_DISTANCE){
        cible = &cibler;
        //std::cout<< "Cible # X : "<< cibler.sprite.getPosition().x << " - Y : " << cibler.sprite.getPosition().y <<std::endl;
    }
    else {
        //std::cout<< "Not Cible"<<std::endl;
        cible = NULL;
    }
}

void Creature::setCible(std::vector<Creature *> cible){
    int index = 0;
    double min = cibleDisctance(*cible[0]);

    for(int i = 1; i < cible.size(); i++){
        double dist = cibleDisctance(*cible[i]);
        if(min > dist)
        {
            min = dist;
            index = i;
        }
    }

    //std::cout<< "Cible MIN : "<< min << " Index : " << index <<std::endl;
    setCible(*cible[index]);
}

bool Creature::hasCible(){
    return cible != NULL ? true : false;
}

void Creature::print() {
    string ecran;
    ecran = "Creature[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante) + "]";
    cout << ecran << endl;
}