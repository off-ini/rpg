//
// Created by benjamin on 02/07/22.
//

#include "Arme.h"

Arme::Arme() : Outil(), point(0), niveau(0) {}

Arme::Arme(string libelle, int point, int niveau) : Outil(libelle), point(point),
                                                    niveau(niveau) {}

int Arme::getPoint() {
    return this->point;
}

int Arme::getNiveau() {
    return this->niveau;
}

void Arme::setPoint(int point) {
    this->point = point;
}

void Arme::setNiveau(int niveau) {
    this->niveau = niveau;
}

void Arme::print() {
    string ecran;
    ecran = "\t\tArme[libelle: " + this->libelle + ", point: " + to_string(this->point) + ", niveau: " +
            to_string(this->niveau) + "]";
    cout << endl << ecran;
}

string Arme::toJson() {
    string type = &(typeid(*this).name()[1]);
    string json;
    json = "{\"type\": \"" + type + "\", \"libelle\": \"" + this->libelle + "\", \"point\": " + to_string(this->point) +
           ", ";
    json += "\"niveau\": " + to_string(this->niveau) + "}";
    return json;
}