//
// Created by benjamin on 02/07/22.
//

#include "Religieux.h"

Religieux::Religieux() : Personnage() {}

Religieux::Religieux(string nom, int niveauSante, int niveauHabilite) : Personnage(nom, niveauSante, niveauHabilite) {}

void Religieux::print() {
    string ecran;
    ecran = "Religieux[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante)
            + ", niveauHabilete:  " + to_string(this->niveauHabilite) + ", ";
    cout << endl << ecran;
    this->sac->print();
    cout << "]" << endl;
}