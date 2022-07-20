//
// Created by infini on 20/07/22.
//

#include "Hache.h"


Hache::Hache() : Arme() {
    libelle = "Hache";
    point = 12;
    niveau = 10;
    load(2,0);
}

Hache::Hache(string libelle, int point, int niveau) : Arme(libelle, point, niveau) {
    libelle = libelle;
    point = point;
    niveau = niveau;
    load(2,0);
}