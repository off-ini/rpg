//
// Created by benjamin on 20/07/22.
//

#include "CleTeleportation.h"

CleTeleportation::CleTeleportation() {
    this->libelle = "Cle de téléportation";
    this->portee = 100;
    this->puissance = 25;
    load(0, 1);
}

CleTeleportation::CleTeleportation(string libelle, int portee, int puissance) : Amulette(libelle, portee, puissance) {
    load(0, 1);
}