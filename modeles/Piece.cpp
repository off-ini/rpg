//
// Created by benjamin on 02/07/22.
//

#include "Piece.h"

Piece::Piece() {
    this->longueur = 9;
    this->largeur = 9;
}

Piece::Piece(int longueur, int largeur, vector<Porte> portes) {
    this->longueur = longueur;
    this->largeur = largeur;
    this->portes = portes;
}

Piece::Piece(const Piece &piece) {
    this->longueur = piece.longueur;
    this->largeur = piece.largeur;
    this->portes = piece.portes;

    for (auto personnage: this->personnages) {
        if (personnage) {
            delete personnage;
        }
    }
    this->personnages.clear();
    this->personnages = piece.personnages;
}

int Piece::getLargeur() {
    return this->largeur;
}

void Piece::setLargeur(int largeur) {
    this->largeur = largeur;
}

int Piece::getLongueur() {
    return this->longueur;
}

void Piece::setLongueur(int longueur) {
    this->longueur = longueur;
}

vector<Porte> Piece::getPortes() {
    return this->portes;
}

void Piece::setPortes(vector<Porte> portes) {
    this->portes = portes;
}

vector<Personnage *> Piece::getPersonnages() {
    return this->personnages;
}

void Piece::setPersonnages(vector<Personnage *> personnages) {
    for (auto personnage: this->personnages) {
        if (personnage) {
            delete personnage;
        }
    }
    this->personnages.clear();
    this->personnages = personnages;
}

Piece::~Piece() {
    for (auto personnage: this->personnages) {
        if (personnage) {
            delete personnage;
        }
    }
    this->personnages.clear();
}

void Piece::print() {
    string ecran;
    ecran = "Piece[longueur: " + to_string(this->longueur) + ", largeur: " + to_string(this->largeur)
            + ", nbrePorte: " + to_string(this->portes.size()) + ",  portes: [";

    for (int i = 0; i < this->portes.size(); i++) {
        if (i == 0) {
            ecran += to_string(this->portes[i].getPosition());
        } else {
            ecran += ", " + to_string(this->portes[i].getPosition());
        }
    }
    ecran += "]]";
    ecran += "\nLes personnages dans la pièce sont: ";
    cout << endl << ecran << endl;

    //Affichage des personnages de la pièces
    for (auto personnage: this->personnages) {
        personnage->print();
    }
}