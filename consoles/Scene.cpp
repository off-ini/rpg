//
// Created by benjamin on 06/07/22.
//

#include "Scene.h"
#include "../modeles/Druide.h"
#include "../modeles/Ouvrier.h"
#include "../modeles/Soldat.h"
#include "../modeles/Religieux.h"
#include "../modeles/Arme.h"
#include "../modeles/Amulette.h"
#include <iostream>
#include <unistd.h>

using namespace std;

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"


Scene::Scene() {}

void Scene::titre() {
    cout << "****************************************" << endl;
    cout << "*" << GRN "   Role Playing Game " << NC "written in " RED << " C++ " NC << " * " << endl;
    cout << "****************************************" << endl << endl;
}

int Scene::choisirPersonnage() {
    int choix;
    cout << "1- Druide" << endl;
    cout << "2- Ouvrier" << endl;
    cout << "3- Guérier" << endl;
    cout << "4- Réligieux" << endl << endl;
    cout << "Veuillez choisir un personnage: ";
    cin >> choix;
    return choix;
}

string Scene::choisirNom() {
    string nom;
    cout << endl << "Veuillez nommez votre personnage: ";
    cin >> nom;
    return nom;
}


void Scene::creationDecor(int numero, string nom) {

    //Création du joueur
    switch (numero) {
        case 1:
            this->joueur = new Druide();
            this->joueur->getSac()->addOutil(new Arme("Epée Glamdring", 50, 5));
            break;
        case 2:
            this->joueur = new Ouvrier();
            this->joueur->getSac()->addOutil(new Arme("Marteau de Thor", 50, 5));
            break;
        case 3:
            this->joueur = new Soldat();
            this->joueur->getSac()->addOutil(new Arme("Epée de Damoclès", 50, 5));
            break;
        default:
            this->joueur = new Religieux();
            this->joueur->getSac()->addOutil(new Arme("Canne de Moise", 50, 5));
    }
    this->joueur->setNom(nom);
    this->joueur->setNiveauHabilite(50);
    this->joueur->setNiveauSante(5);

    //Affichage du joueur dans la console pour voir qu'il est convenablement crée
    this->joueur->print();

    //Création du batiment, des pieces et des portes
    cout << endl << "Veillez patienter un instant..." << endl;
    sleep(2);

    //Portes
    vector<Porte> portes;
    portes.push_back(Porte(0));
    portes.push_back(Porte(1));

    //Personnages
    vector<Personnage *> personnages;
    Personnage *personnage = new Druide("Saroumane", 5, 60);
    Sac *sac = new Sac();
    sac->addOutil(new Amulette("Baton du magicien", 5, 10));
    personnage->setSac(sac);
    personnages.push_back(personnage);

    //Pieces
    vector<Piece*> pieces;
    Piece piece(10, 10, portes);
    piece.setPersonnages(personnages);
    pieces.push_back(&piece);

    this->batiment = new Batiment(pieces);
    pieceCourante = 0;

    cout << endl << "Création du décor terminé." << endl;
    sleep(2);
}


void Scene::presentePiece() {
    string presentation;
    presentation = "\n" + this->joueur->getNom() + ", vous entrez dans la piece n°" + to_string(pieceCourante + 1) +
                   "du batiment.";
    presentation += "\nLongueur x largeur: " + to_string(this->batiment->getPieces()[0]->getLongueur()) + "m x " +
                    to_string(this->batiment->getPieces()[0]->getLargeur()) + "m.";
    presentation += "\nEnnemi présent: \n";
    for (auto piece: this->batiment->getPieces()) {
        int i = 0;
        for (auto personnage: piece->getPersonnages()) {
            presentation += to_string(i + 1) + " - " + personnage->getNom();
        }
    }
}

void Scene::choixAdversaire() {

}