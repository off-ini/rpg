//
// Created by benjamin on 02/07/22.
//

#include "Ouvrier.h"

Ouvrier::Ouvrier() : Personnage() {}

Ouvrier::Ouvrier(string nom, int niveauSante, int niveauHabilite) : Personnage(nom, niveauSante, niveauHabilite) {}

void Ouvrier::print() {
    string ecran;
    ecran = "Ouvrier[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante)
            + ", niveauHabilete:  " + to_string(this->niveauHabilite) + ", ";
    cout << endl << ecran;
    this->sac->print();
    cout << "]" << endl;
}