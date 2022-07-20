//
// Created by infini on 20/07/22.
//

#include "Bouclier.h"


Bouclier::Bouclier() : Arme() {
    libelle = "Bouclier";
    point = 10;
    niveau = 5;
    load(0,0);
}

Bouclier::Bouclier(string libelle, int point, int niveau) : Arme(libelle, point, niveau) {
    libelle = libelle;
    point = point;
    niveau = niveau;
    load(0,0);
}