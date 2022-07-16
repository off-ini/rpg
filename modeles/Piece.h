//
// Created by benjamin on 02/07/22.
//

#ifndef RPG_PIECE_H
#define RPG_PIECE_H

#include <vector>
#include "GameObject.h"
#include "Porte.h"
#include "Personnage.h"
#include <string>
#include <iostream>

using namespace std;

class Piece : public GameObject {
private:
    int longueur;
    int largeur;
    vector<Porte> portes;//Une pièce ne peut avoir au maximum que quatre portes
    vector<Personnage *> personnages;

public:
    Piece();

    Piece(int longeur, int largeur, vector<Porte> portes);

    Piece(const Piece &piece);

    int getLongueur();

    void setLongueur(int longueur);

    int getLargeur();

    void setLargeur(int largeur);

    void setPortes(vector<Porte> portes);

    vector<Porte> getPortes();

    void setPersonnages(vector<Personnage *> personnages);

    vector<Personnage *> getPersonnages();

    ~Piece();

    void print();

};


#endif //RPG_PIECE_H
