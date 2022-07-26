//
// Created by benjamin on 20/07/22.
//

#include "Feu.h"

Feu::Feu() {
    this->libelle = "Feu";
    this->puissance = 20;
    this->portee = 7;
    load(1, 1);
}

Feu::Feu(string libelle, int portee, int puissance) : Amulette(libelle, portee, puissance) {
    load(1, 1);
}
