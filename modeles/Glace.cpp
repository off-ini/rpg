//
// Created by benjamin on 20/07/22.
//

#include "Glace.h"

Glace::Glace() : Amulette() {
    this->libelle = "Glace";
    this->puissance = 15;
    this->portee = 5;
    load(2, 1);
}

Glace::Glace(string libelle, int portee, int puissance) : Amulette(libelle, portee, puissance) {
    load(2, 1);
}
