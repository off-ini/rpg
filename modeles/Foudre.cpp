//
// Created by benjamin on 20/07/22.
//

#include "Foudre.h"

Foudre::Foudre() {
    this->libelle = "Foudre";
    this->puissance = 23;
    this->portee = 5;
    //load(3, 1);
}

Foudre::Foudre(string libelle, int portee, int puissance) : Amulette(libelle, portee, puissance) {
    //load(3, 1);
}
