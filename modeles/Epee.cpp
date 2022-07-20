//
// Created by infini on 20/07/22.
//

#include "Epee.h"

Epee::Epee() : Arme() {
    libelle = "Epee";
    point = 10;
    niveau = 10;
    load(1,0);
}

Epee::Epee(string libelle, int point, int niveau) : Arme(libelle, point, niveau) {
    libelle = libelle;
    point = point;
    niveau = niveau;
    load(1,0);
}