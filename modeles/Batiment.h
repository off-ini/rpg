//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_BATIMENT_H
#define RPG_BATIMENT_H

#include "GameObject.h"
#include "Piece.h"
#include <vector>

using namespace std;

class Batiment : public GameObject {
private:
    vector<Piece *> pieces;

public:
    Batiment();

    Batiment(vector<Piece *> pieces);

    vector<Piece *> getPieces();

    void addPiece(Piece piece);

    void setPiece(vector<Piece *> pieces);

};


#endif //RPG_BATIMENT_H
