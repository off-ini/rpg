//
// Created by benjamin on 20/07/22.
//

#include "PotionRegeneration.h"

PotionRegeneration::PotionRegeneration() {
    this->libelle = "Potion";
    this->point = 25;
    load(0, 2);
}

PotionRegeneration::PotionRegeneration(int point) {
    this->libelle = "Potion";
    this->point = point;
}

PotionRegeneration::PotionRegeneration(string libelle, int point) : Potion(libelle, point) {
    load(0, 2);
}