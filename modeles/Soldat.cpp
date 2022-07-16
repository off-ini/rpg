//
// Created by benjamin on 02/07/22.
//

#include "Soldat.h"

Soldat::Soldat() : Personnage() {}

Soldat::Soldat(string nom, int niveauSante, int niveauHabilite) : Personnage(nom, niveauSante, niveauHabilite) {}

void Soldat::print(void) {
    string ecran = "Soldat[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante)
                   + ", niveauHabilete:  " + to_string(this->niveauHabilite) + ", ";
    cout << endl << ecran;
    this->sac->print();
    cout << "]" << endl;
}