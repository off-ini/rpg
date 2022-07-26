//
// Created by benjamin on 02/07/22.
//

#include "Outil.h"

Outil::Outil() {
    this->libelle = "";
}

Outil::Outil(string libelle) {
    this->libelle = libelle;
}

string Outil::getLibelle() {
    return this->libelle;
}

void Outil::setLibelle(string libelle) {
    this->libelle = libelle;
}

void Outil::load(int x, int y){
    if(!textureMini.loadFromFile("./assets/sprites/outils.png", IntRect(x * 32, y * 32,  32, 32))){
        perror("Load erreur");
    }
    textureMini.setSmooth(true);
    spriteMini.setTexture(textureMini);

    rectangle.setSize(Vector2f(36, 36));
    rectangle.setFillColor(Color::White);

    rectangle.setPosition(0,0);
    spriteMini.setPosition(2,2);
}

void Outil::setPosition(float x, float y){
    rectangle.setPosition(x, y);
    spriteMini.setPosition(x+2, y+2);
}

bool Outil::onMouseEnter(RenderWindow& window){
    Vector2i mousePosition = sf::Mouse::getPosition(window);

    FloatRect boundingBox = rectangle.getGlobalBounds();

    Vector2f point(mousePosition.x, mousePosition.y);
    if (boundingBox.contains(point))
        return true;
    else return false;
}

void Outil::setRectColor(Color color){
    rectangle.setFillColor(color);
}

void Outil::print() {
    cout << endl << "\tOutil[libelle: " + libelle + "]";
}

string Outil::toJson() {
    string json;
    json = "{\"libelle\": \"" + libelle + "\"}";
    return json;
}