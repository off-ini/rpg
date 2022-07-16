//
// Created by benjamin on 02/07/22.
//

#include "Porte.h"

Porte::Porte() : position(0) {}

Porte::Porte(int position) {
    this->position = position;
}

int Porte::getPosition() {
    return this->position;
}

void Porte::setPosition(int position) {
    this->position = position;
}
