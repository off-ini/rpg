//
// Created by benjamin on 02/07/22.
//

#include "Amulette.h"

Amulette::Amulette() : Outil(), portee(0), puissance(0) {}

Amulette::Amulette(string libelle, int portee, int puissance) : Outil(libelle), portee(portee),
                                                                puissance(puissance) {}

int Amulette::getNiveau() {
    return this->portee;
}

int Amulette::getPoint() {
    return this->puissance;
}

void Amulette::setNiveau(int portee) {
    this->portee = portee;
}

void Amulette::setPoint(int puissance) {
    this->puissance = puissance;
}

void Amulette::print() {
    string ecran;
    ecran = "\t\tAmulette[libelle: " + this->libelle + ", portee: " + to_string(this->portee) + ", puissance: " +
            to_string(this->puissance) + "]";
    cout << endl << ecran;
}

string Amulette::toJson() {
    string type = &(typeid(*this).name()[1]);
    string json;
    json = "{\"type\": \"" + type + "\", \"libelle\": \"" + this->libelle + "\", \"portee\": " +
           to_string(this->portee) + ", ";
    json += "\"puissance\": " + to_string(this->puissance) + "}";
    return json;
}