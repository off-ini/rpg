//
// Created by benjamin on 02/07/22.
//

#include "Religieux.h"
#include "../utils/distribution.h"
#include "Bouclier.h"
#include "Epee.h"
#include "Foudre.h"
#include "PotionRegeneration.h"

Religieux::Religieux(): Personnage("Ouvrier", 90, 3) {
    int number = Gen::distNumber(7, 8);
    load(number);
    getSac()->addOutil(new Bouclier);
    getSac()->addOutil(new Epee);
    getSac()->addOutil(new Foudre);
    getSac()->addOutil(new PotionRegeneration(15));
}

Religieux::Religieux(string nom, int niveauSante, int niveauHabilite) : Personnage(nom, niveauSante, niveauHabilite) {}

void Religieux::print() {
    string ecran;
    ecran = "Religieux[nom: " + this->nom + ", niveauSante:  " + to_string(this->niveauSante)
            + ", niveauHabilete:  " + to_string(this->niveauHabilite) + ", ";
    cout << endl << ecran;
    this->sac->print();
    cout << "]" << endl;
}

string Religieux::toJson() {
    string type = &(typeid(*this).name()[1]);
    string json;
    json = "{\"type\": \"" + type + "\", \"nom\": \"" + this->nom + "\", \"niveauSante\": " +
           to_string(this->niveauSante)
           + ", \"niveauHabilete\": " + to_string(this->niveauHabilite) + ", \"sac\": [";
    json += this->sac->toJson();
    json += "]}";
    return json;
}