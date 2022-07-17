//
// Created by benjamin on 02/07/22.
//

#include "Batiment.h"

Batiment::Batiment() {}

Batiment::Batiment(vector<Piece *> pieces) {
    this->pieces = pieces;
}

void Batiment::addPiece(Piece piece) {
    //Vérifier que piece n'est pas déjà dans le batiment
    this->pieces.push_back(&piece);
}

vector<Piece *> Batiment::getPieces() {
    return this->pieces;
}

void Batiment::setPiece(vector<Piece *> pieces) {
    this->pieces = pieces;
}