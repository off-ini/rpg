//
// Created by infini on 20/07/22.
//

#include "Massue.h"

Massue::Massue() : Arme() {
    libelle = "Massue";
    point = 15;
    niveau = 5;
    load(4,0);
}

Massue::Massue(string libelle, int point, int niveau) : Arme(libelle, point, niveau) {
    load(4,0);
}