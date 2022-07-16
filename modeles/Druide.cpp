//
// Created by benjamin on 02/07/22.
//

#include "Druide.h"

Druide::Druide() : Personnage() {}

Druide::Druide(string nom, int niveauSante, int niveauHabilite) : Personnage(nom, niveauSante, niveauHabilite) {}

void Druide::print() {
    string ecran;
    ecran = "Druide[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante)
            + ", niveauHabilete:  " + to_string(this->niveauHabilite) + ", ";
    cout << endl << ecran;
    this->sac->print();
    cout << "]" << endl;
}