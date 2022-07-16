//
// Created by benjamin on 06/07/22.
//

#ifndef RPG_SCENE_H
#define RPG_SCENE_H

#include "../modeles/Personnage.h"
#include "../modeles/Batiment.h"
#include <string>
#include <vector>

using namespace std;

//Cette class contiendra des méthodes statiques de simulation du jeu en console
class Scene {

private:
    Personnage *joueur;
    Batiment *batiment;
    int pieceCourante;

public:
    Scene();

    void titre();

    int choisirPersonnage();

    string choisirNom(void);

    void creationDecor(int numero, string nom);

    void presentePiece();

    void choixAdversaire();
};


#endif //RPG_SCENE_H
