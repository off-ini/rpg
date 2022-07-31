//
// Created by benjamin on 02/07/22.
//

#include "Druide.h"
#include "../utils/distribution.h"
#include "Bouclier.h"
#include "Feu.h"
#include "Foudre.h"
#include "PotionRegeneration.h"
#include "Glace.h"

Druide::Druide(): Personnage("Druide", 50, 2){
    int number = Gen::distNumber(3, 4);
    load(number);
    getSac()->addOutil(new Bouclier);
    getSac()->addOutil(new Feu);
    getSac()->addOutil(new Glace);
    getSac()->addOutil(new Foudre);
    getSac()->addOutil(new PotionRegeneration(15));
}

Druide::Druide(string nom, int niveauSante, int niveauHabilite) : Personnage(nom, niveauSante, niveauHabilite) {}

void Druide::print() {
    string ecran;
    ecran = "Druide[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante)
            + ", niveauHabilete:  " + to_string(this->niveauHabilite) + ", ";
    cout << endl << ecran;
    this->sac->print();
    cout << "]" << endl;
}

string Druide::toJson() {
    string type = &(typeid(*this).name()[1]);
    string json;
    json = "{\"type\": \"" + type + "\", \"nom\": \"" + this->nom + "\", \"niveauSante\": " +
           to_string(this->niveauSante)
           + ", \"niveauHabilete\": " + to_string(this->niveauHabilite) + ", \"sac\": [";
    json += this->sac->toJson();
    json += "]}";
    return json;
}