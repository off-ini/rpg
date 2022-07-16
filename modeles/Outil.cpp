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

void Outil::print() {
    cout << endl << "\tOutil[libelle: " + libelle + "]" << endl;
}