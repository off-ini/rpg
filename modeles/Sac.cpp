//
// Created by benjamin on 02/07/22.
//

#include "Sac.h"

//Constructeur par défaut
Sac::Sac() {}

//Constructeur avec parametre
Sac::Sac(vector<Outil *> outils) {
    this->outils = outils;
}

//Constructeur de copie
Sac::Sac(const Sac &sac) {
    //Supprimer des outils de sac
    for (auto outil: this->outils) {
        if (outil) {
            delete outil;
        }
    }
    this->outils.clear();

    //Copie des outils du sac passé en paramètre
    for (int i = 0; i < sac.outils.size(); i++) {
        this->outils.push_back(sac.outils[i]);
    }
}

void Sac::addOutil(Outil *outil) {
    this->outils.push_back(outil);
}

vector<Outil *> Sac::getOutils() {
    return this->getOutils();
}

void Sac::setOutils(vector<Outil *> outils) {
    this->outils = outils;
}

Sac &Sac::operator=(const Sac &sac) {
    //Supprission des outils de sac
    for (auto outil: this->outils) {
        if (outil) {
            delete outil;
        }
    }
    this->outils.clear();

    //Copie des outils du sac passé en paramètre
    for (int i = 0; i < sac.outils.size(); i++) {
        this->outils.push_back(sac.outils[i]);
    }

    return *this;
}

Sac::~Sac() {
    for (auto outil: this->outils) {
        if (outil) {
            delete outil;
        }
    }
    this->outils.clear();
}

void Sac::print() {
    string ecran;
    ecran = "\tSac[nbreOutils: " + to_string(this->outils.size()) + ", ";
    cout << endl << ecran;
    for (int i = 0; i < this->outils.size(); i++) {
        cout << "\t";
        this->outils[i]->print();
    }
    cout << "\t]" << endl;
}
