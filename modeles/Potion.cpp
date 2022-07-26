//
// Created by benjamin on 02/07/22.
//

#include "Potion.h"

Potion::Potion() : Outil(), point(0) {}

Potion::Potion(string libelle, int point) : Outil(libelle), point(point) {}

int Potion::getPoint() {
    return this->point;
}

void Potion::setPoint(int point) {
    this->point = point;
}

void Potion::print() {
    string ecran;
    ecran = "\t\tPotion[libelle: " + this->libelle + ", point: " + to_string(this->point) + "]";
    cout << endl << ecran;
}

string Potion::toJson() {
    string type = &(typeid(*this).name()[1]);
    string json;
    json = "{\"type\": \"" + type + "\", \"libelle\": \"" + this->libelle + "\", \"point\": " + to_string(this->point) +
           "}";
    return json;
}