//
// Created by benjamin on 02/07/22.
//

#include "Ouvrier.h"
#include "../utils/distribution.h"
#include "Bouclier.h"
#include "Hache.h"
#include "Massue.h"
#include "PotionRegeneration.h"

Ouvrier::Ouvrier(): Personnage("Ouvrier", Gen::distNumber(50, 90), Gen::distNumber(2, 5)) {
    int number = Gen::distNumber(5, 6);
    load(number);
    getSac()->addOutil(new Bouclier);
    getSac()->addOutil(new Hache);
    getSac()->addOutil(new Massue);
    getSac()->addOutil(new PotionRegeneration(15));
}

Ouvrier::Ouvrier(string nom, int niveauSante, int niveauHabilite) : Personnage(nom, niveauSante, niveauHabilite) {}

void Ouvrier::print() {
    string ecran;
    ecran = "Ouvrier[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante)
            + ", niveauHabilete:  " + to_string(this->niveauHabilite) + ", ";
    cout << endl << ecran;
    this->sac->print();
    cout << "]" << endl;
}

string Ouvrier::toJson() {
    string type = &(typeid(*this).name()[1]);
    string json;
    json = "{\"type\": \"" + type + "\", \"nom\": \"" + this->nom + "\", \"niveauSante\": " +
           to_string(this->niveauSante)
           + ", \"niveauHabilete\": " + to_string(this->niveauHabilite) + ", \"sac\": [";
    json += this->sac->toJson();
    json += "]}";
    return json;
}